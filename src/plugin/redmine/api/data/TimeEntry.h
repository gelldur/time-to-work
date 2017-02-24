//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <chrono>
#include <string>

struct TimeEntry
{
	TimeEntry()
	{
	}

	TimeEntry(int issueId, int activityId, std::chrono::minutes time, const std::string& comment)
			: issueId(issueId)
			, activityId(activityId)
			, time(time)
			, comment(comment)
	{
	}

	int issueId = 0;
	int activityId = 0;
	std::chrono::minutes time;
	std::string comment;

	float getHours() const
	{
		return time.count() / 60.F;
	}

	bool isValid() const
	{
		return issueId > 0 && activityId > 0 && getHours() > 0;
	}

	std::string getComment() const
	{
		if (comment.length() > 255)
		{
			return comment.substr(0, 252) + "...";
		}
		return comment;
	}
};


