//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#include "TimeEntries.h"
//////////////////////////////////

#include <Poco/URI.h>

#include <Poco/JSON/Parser.h>

std::unique_ptr<Poco::Net::HTTPRequest> TimeEntries::requestLogTime(const std::string& apiKey)
{
	Poco::URI uri{"/time_entries.json"};

	auto request = std::make_unique<Poco::Net::HTTPRequest>(Poco::Net::HTTPRequest::HTTP_POST
															, uri.toString()
															, Poco::Net::HTTPMessage::HTTP_1_1);
	request->setContentType("application/json");
	request->add("X-Redmine-API-Key", apiKey);
	request->setChunkedTransferEncoding(true);

	return std::move(request);
}

void TimeEntries::logTimeBody(std::ostream& body, const TimeEntry& timeEntry)
{
	Poco::JSON::Object timeEntryJson;
	timeEntryJson.set("issue_id", timeEntry.issueId);
	timeEntryJson.set("activity_id", timeEntry.activityId);
	timeEntryJson.set("hours", timeEntry.time);
	timeEntryJson.set("comments", timeEntry.comment);

	Poco::JSON::Object logTime;
	logTime.set("time_entry", timeEntryJson);

	Poco::JSON::Stringifier stringifier;
	stringifier.condense(logTime, body);
}

bool TimeEntries::processLogTime(const Poco::Net::HTTPResponse& response, std::istream& body)
{
	//TODO handle errors like:
	//{"errors":["Activity cannot be blank","Project cannot be blank","Project is invalid","Hours cannot be blank"]}
	std::cout << body.rdbuf() << std::endl;
	return false;
}
