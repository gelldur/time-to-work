//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#include "AppController.h"
//////////////////////////////////

#include <iostream>
#include <sstream>

AppController::AppController(QObject* parent)
		: inherited(parent)
{
	std::cout << parent << std::endl;
}

QString AppController::getTimeWorking() const
{
	return QString::fromStdString(formatWorkingTime());
}

void AppController::onStartWorking()
{
	_startWork = std::chrono::system_clock::now();
}

void AppController::onStopWorking()
{
	_startWork = {};
}

std::string AppController::formatWorkingTime() const
{
	if (_startWork.time_since_epoch().count() < 1LL)
	{
		return "";//not working now
	}

	auto now = std::chrono::system_clock::now();
	auto duration = now - _startWork;

	std::stringstream stream;
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	if (hours.count() > 0)
	{
		duration -= hours;
		stream << hours.count() << "h ";
	}
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	if (minutes.count() > 0)
	{
		duration -= minutes;
		stream << minutes.count() << "m ";
	}
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	if (seconds.count() > 0)
	{
		duration -= seconds;
		stream << seconds.count() << "s";
	}

	auto text = stream.str();
	if (text.empty())
	{
		return "0s";
	}

	return text;
}
