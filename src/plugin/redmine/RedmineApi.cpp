//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#include "RedmineApi.h"
//////////////////////////////////

#include <iostream>

#include <plugin/redmine/api/Enumerations.h>
#include <plugin/redmine/api/TimeEntries.h>

RedmineApi::RedmineApi(const std::string& serverUrl, const std::string& apiKey)
		: _apiKey(apiKey)
		, _session(serverUrl
				   , Poco::Net::HTTPSClientSession::HTTPS_PORT
				   , Poco::Net::Context::Ptr(new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", ""
																	, Poco::Net::Context::VERIFY_NONE, 9, false
																	, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH")))
{
}

std::vector<WorkActivity> RedmineApi::getTimeEntryActivities()
{
	Enumerations api;
	auto request = api.requestTimeEntryActivities(_apiKey);

	try
	{
		_session.sendRequest(*request);

		Poco::Net::HTTPResponse response;
		auto& body = _session.receiveResponse(response);

		return api.processTimeEntryActivities(response, body);
	}
	catch (const std::exception& ex)
	{
		logException(ex);
		throw;
	}
}

void RedmineApi::logException(const std::exception& ex)
{
	//TODO later
	//		Reporter reporter;
	//		reporter.handle(Fail::where(__FILE__, __func__, __LINE__), urlBuilder.build() + "\n" + ex.what()
	//						, connection.get());
}

bool RedmineApi::logTime(const TimeEntry& timeEntry)
{
	TimeEntries api;
	auto request = api.requestLogTime(_apiKey);
	try
	{
		api.logTimeBody(_session.sendRequest(*request), timeEntry);

		Poco::Net::HTTPResponse response;
		auto& body = _session.receiveResponse(response);

		request->write(std::cout);
		response.write(std::cout);

		return api.processLogTime(response, body);
	}
	catch (const std::exception& ex)
	{
		logException(ex);
		throw;
	}
}
