//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <chrono>

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtConcurrent>

#include <plugin/redmine/RedmineApi.h>

class AppController : public QObject
{
Q_OBJECT
	using inherited = QObject;

public:
	explicit AppController(QObject* parent = nullptr);

	Q_INVOKABLE QString getTimeWorking() const;

signals:
	void activitiesDownloaded(QVariantList activitesLabels);
	void timeLoged(int status, QString message);
	void errorMessage(QString message);

public slots:
	void onStartWorking();
	void onStopWorking(QVariantMap viewData);

private slots:
	void onActivitiesDownloaded();
	void onTimeLogDone();

private:
	std::chrono::system_clock::time_point _startWork;
	std::vector<WorkActivity> _workActivities;

	RedmineApi _redmineApi;

	QFutureWatcher<std::vector<WorkActivity>> _watcherActivities;
	QFutureWatcher<bool> _watcherTimeLog;

	std::string formatWorkingTime() const;
};


