//
// Created by Dawid Drozd aka Gelldur on 23.02.17.
//
#pragma once

#include <string>

struct WorkActivity
{
	WorkActivity(unsigned int id, const std::string& name)
			: id(id)
			, name(name)
	{
	}

	unsigned id;
	std::string name;
};


