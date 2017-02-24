//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#include "AppController.h"
//////////////////////////////////

#include <iostream>
#include <sstream>

AppController::AppController(QObject* parent)
		: inherited(parent)
		, _redmineApi("redmine.milosolutions.com", "87f71e998562d0f05b1b2400882060edf8b754fc")
{
	connect(&_watcherActivities, SIGNAL(finished()), this, SLOT(onActivitiesDownloaded()));
	connect(&_watcherTimeLog, SIGNAL(finished()), this, SLOT(onTimeLogDone()));

	auto future = QtConcurrent::run([this]()
									{
										qDebug() << "Downloading activities";
										try
										{
											return _redmineApi.getTimeEntryActivities();
										}
										catch (std::exception ex)
										{
											qCritical() << ex.what();
											return std::vector<WorkActivity>{};
										}
									});
	_watcherActivities.setFuture(future);
}

QString AppController::getTimeWorking() const
{
	return QString::fromStdString(formatWorkingTime());
}

void AppController::onStartWorking()
{
	qDebug() << "onStartWorking";
	_startWork = std::chrono::system_clock::now();
}

void AppController::onStopWorking(QVariantMap viewData)
{
	qDebug() << "onStopWorking" << viewData;

	auto now = std::chrono::system_clock::now();
	auto workDuration = std::chrono::duration_cast<std::chrono::minutes>(now - _startWork);

	bool isOk = false;

	TimeEntry timeEntry;
	timeEntry.issueId = viewData["issue"].toInt(&isOk);
	if (isOk == false)
	{
		emit errorMessage("Invalid issue");
		return;
	}
	timeEntry.activityId = viewData["activity"].toInt(&isOk);
	if (isOk == false || _workActivities.size() <= (unsigned) timeEntry.activityId)
	{
		emit errorMessage("Invalid activity index");
		return;
	}
	timeEntry.activityId = _workActivities.at(timeEntry.activityId).id;
	timeEntry.time = workDuration;
	timeEntry.comment = viewData["comment"].toString().toStdString();

	auto future = QtConcurrent::run([this, timeEntry]()
									{
										qDebug() << "Sending time log";
										try
										{
											return _redmineApi.logTime(timeEntry);;
										}
										catch (std::exception ex)
										{
											qCritical() << ex.what();
											return false;
										}
									});
	_watcherTimeLog.setFuture(future);

	_startWork = {};
}

std::string AppController::formatWorkingTime() const
{
	if (_startWork.time_since_epoch().count() < 1LL)
	{
		return "";//not working now
	}

	auto now = std::chrono::system_clock::now();
	auto workDuration = now - _startWork;

	std::stringstream stream;
	auto hours = std::chrono::duration_cast<std::chrono::hours>(workDuration);
	if (hours.count() > 0)
	{
		workDuration -= hours;
		stream << hours.count() << "h ";
	}
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(workDuration);
	if (minutes.count() > 0)
	{
		workDuration -= minutes;
		stream << minutes.count() << "m ";
	}
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(workDuration);
	if (seconds.count() > 0)
	{
		workDuration -= seconds;
		stream << seconds.count() << "s";
	}

	auto text = stream.str();
	if (text.empty())
	{
		return "0s";
	}

	return text;
}

void AppController::onActivitiesDownloaded()
{
	qDebug() << "Downloaded activities";
	_workActivities = _watcherActivities.future().result();

	QVariantList activitesLabels;
	for (auto& element : _workActivities)
	{
		activitesLabels << QString::fromStdString(element.name);
	}
	emit activitiesDownloaded(activitesLabels);
}

void AppController::onTimeLogDone()
{
	emit timeLoged(_watcherTimeLog.future().result(), "Something cool");
}
