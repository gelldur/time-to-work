//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <chrono>

#include <QObject>
#include <QtQuick/QQuickView>

class AppController : public QObject
{
Q_OBJECT
	using inherited = QObject;

public:
	explicit AppController(QObject* parent = nullptr);

	Q_INVOKABLE QString getTimeWorking() const;

	Q_INVOKABLE void onStartWorking();
	Q_INVOKABLE void onStopWorking();

private:
	std::chrono::system_clock::time_point _startWork;

	std::string formatWorkingTime() const;
};


