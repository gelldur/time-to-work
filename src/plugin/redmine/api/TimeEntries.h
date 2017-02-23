//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <sstream>
#include <memory>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <plugin/redmine/api/data/TimeEntry.h>

class TimeEntries
{
public:
	std::unique_ptr<Poco::Net::HTTPRequest> requestLogTime(const std::string& apiKey);
	void logTimeBody(std::ostream& body, const TimeEntry& timeEntry);
	bool processLogTime(const Poco::Net::HTTPResponse& response, std::istream& body);
};


