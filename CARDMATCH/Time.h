#pragma once

#include "TimeManager.h"

class Time
{
	friend class TimeManager;

private:
	Time(long, long, bool);
	~Time() = default;

	long start;
	long pause;
	long lag;
	bool isPerfCounter;
};