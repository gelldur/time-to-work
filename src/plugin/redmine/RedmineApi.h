//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <string>
#include <vector>

#include <Poco/Net/HTTPSClientSession.h>

#include <plugin/redmine/api/data/WorkActivity.h>
#include <plugin/redmine/api/data/TimeEntry.h>

/**
 * REST API docs available at: http://www.redmine.org/projects/redmine/wiki/Rest_api
 */
class RedmineApi
{
public:
	RedmineApi(const std::string& serverUrl, const std::string& apiKey);

	std::vector<WorkActivity> getTimeEntryActivities();
	bool logTime(const TimeEntry& timeEntry);

private:
	const std::string _apiKey;
	Poco::Net::HTTPSClientSession _session;

	void logException(const std::exception& ex);
};


