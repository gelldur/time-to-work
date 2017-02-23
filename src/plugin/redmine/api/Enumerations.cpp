//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#include "Enumerations.h"
//////////////////////////////////

#include <Poco/URI.h>

#include <Poco/JSON/Parser.h>

std::unique_ptr<Poco::Net::HTTPRequest> Enumerations::requestTimeEntryActivities(const std::string& apiKey)
{
	Poco::URI uri{"/enumerations/time_entry_activities.json"};

	auto request = std::make_unique<Poco::Net::HTTPRequest>(Poco::Net::HTTPRequest::HTTP_GET
															,uri.toString()
															,Poco::Net::HTTPMessage::HTTP_1_1);

	request->add("X-Redmine-API-Key", apiKey);
	return std::move(request);
}

std::vector<WorkActivity> Enumerations::processTimeEntryActivities(const Poco::Net::HTTPResponse& response
		, std::istream& body)
{
	Poco::JSON::Parser parser;

	auto jsonData = parser.parse(body);

	auto& data = jsonData.extract<Poco::JSON::Object::Ptr>();
	auto timeEntryActivitiesJson = data->getArray("time_entry_activities");

	std::vector<WorkActivity> timeEntryActivities;
	timeEntryActivities.reserve(timeEntryActivities.size());

	for (auto& entry : *timeEntryActivitiesJson)
	{
		auto& objectEntry = entry.extract<Poco::JSON::Object::Ptr>();
		timeEntryActivities.emplace_back(objectEntry->get("id").convert<decltype(WorkActivity::id)>()
										 , objectEntry->get("name").convert<decltype(WorkActivity::name)>());
	}

	return timeEntryActivities;
}
