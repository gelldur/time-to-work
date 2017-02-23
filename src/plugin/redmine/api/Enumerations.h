//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <vector>
#include <sstream>
#include <memory>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

#include <plugin/redmine/api/data/WorkActivity.h>

class Enumerations
{
public:
	std::unique_ptr<Poco::Net::HTTPRequest> requestTimeEntryActivities(const std::string& apiKey);
	std::vector<WorkActivity> processTimeEntryActivities(const Poco::Net::HTTPResponse& response, std::istream& body);
};


