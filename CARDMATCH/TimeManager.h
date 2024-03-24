#pragma once

#include <iostream>
#include <map>
#include <string>

#include "SDL.h"

#include "Time.h"

class Time;

class TimeManager
{
	typedef Uint32 (*Callback)(Uint32, void*);

public:
	~TimeManager();

	static TimeManager* getInstance();
	static void removeInstance();

	bool destroy();

	bool addTimer(const std::string&, bool = false);
	bool addPerfCounter(const std::string&, bool = false);

	bool remove(const std::string&);

	bool addTimeout(Callback, long, void*, const std::string & = "", bool = false);
	bool removeTimeout(const std::string&);

	bool start(const std::string&);
	bool pause(const std::string&);
	bool resume(const std::string&);
	bool reset(const std::string&);
	bool toggle(const std::string&);

	long get(const std::string&);
	long getPausedTime(const std::string&);

	long getPerfFreq();
	long ticksSinceStart();
	long perfSinceStart();

private:
	TimeManager() = default;

	static TimeManager* instance;

	std::map<std::string, Time*> timers;
	std::map<std::string, long> callbacks;
};

