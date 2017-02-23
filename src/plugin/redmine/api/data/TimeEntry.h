//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <string>

struct TimeEntry
{
	TimeEntry(int issueId, int activityId, float time, const std::string& comment)
			: issueId(issueId)
			, activityId(activityId)
			, time(time)
			, comment(comment)
	{
	}

	int issueId;
	int activityId;
	float time;
	std::string comment;
};


