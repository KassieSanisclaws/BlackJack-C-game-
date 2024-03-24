#include "TimeManager.h"

TimeManager::~TimeManager()
{
	for (auto i : timers)
		delete i.second;

	for (auto i : callbacks)
		removeTimeout(i.first);
}

TimeManager* TimeManager::getInstance()
{
	if (instance == 0)
		instance = new TimeManager();

	return instance;
}

void TimeManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

bool TimeManager::destroy()
{
	return true;
}

bool TimeManager::addTimer(const std::string& tID, bool startPaused)
{
	if (timers.find(tID) != timers.end())
		return false;

	long currentTime = ticksSinceStart();
	Time* newT = new Time(currentTime, startPaused ? currentTime : 0, false);

	timers.insert({ tID, newT });

	std::cout << "Adding timer " << tID << "..." << std::endl;

	return true;
}

bool TimeManager::addPerfCounter(const std::string& tID, bool startPaused)
{
	if (timers.find(tID) != timers.end())
		return false;

	long currentTime = perfSinceStart();
	Time* newPC = new Time(currentTime, startPaused ? currentTime : 0, true);

	timers.insert({ tID, newPC });

	return true;
}

bool TimeManager::remove(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	delete entry->second;

	timers.erase(entry);

	std::cout << "Removing timer " << tID << "..." << std::endl;

	return true;
}

bool TimeManager::addTimeout(Callback callback, long delay, void* param, const std::string& tID, bool save)
{
	if (save && tID == "")
		return false;

	if (save && callbacks.find(tID) != callbacks.end())
		return false;

	SDL_TimerID result = SDL_AddTimer(delay, (SDL_TimerCallback)callback, param);

	if (result == 0)
		return false;

	if (save)
		callbacks.insert({ tID, result });

	return true;
}

bool TimeManager::removeTimeout(const std::string& tID)
{
	auto entry = callbacks.find(tID);

	if (entry == callbacks.end())
		return false;

	int result = SDL_RemoveTimer(entry->second);

	callbacks.erase(entry);

	if (result == 0)
		return false;

	return true;
}

bool TimeManager::start(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	if (!entry->second->pause)
		return false;

	if (entry->second->isPerfCounter)
		entry->second->lag = perfSinceStart() - entry->second->pause - entry->second->start;
	else
		entry->second->lag = ticksSinceStart() - entry->second->pause - entry->second->start;

	entry->second->pause = 0;

	std::cout << "Stating timer " << tID << "..." << std::endl;

	return true;
}

bool TimeManager::pause(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	if (entry->second->pause)
		return false;

	if (entry->second->isPerfCounter)
		entry->second->pause = perfSinceStart() - entry->second->pause - entry->second->start;
	else
		entry->second->pause = ticksSinceStart() - entry->second->pause - entry->second->start;

	std::cout << "Pausing timer " << tID << "..." << std::endl;

	return true;
}

bool TimeManager::resume(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	std::cout << "Resuming timer " << tID << "..." << std::endl;

	return start(tID);
}

bool TimeManager::reset(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	if (entry->second->isPerfCounter)
		entry->second->start = perfSinceStart();
	else
		entry->second->start = ticksSinceStart();

	entry->second->pause = 0;
	entry->second->lag = 0;

	std::cout << "Resetting timer " << tID << "..." << std::endl;

	return true;
}

bool TimeManager::toggle(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return false;

	if (entry->second->pause)
		resume(tID);
	else
		pause(tID);

	return true;
}

long TimeManager::get(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return -1;

	if (entry->second->pause)
		return entry->second->pause;

	if (entry->second->isPerfCounter)
		return perfSinceStart() - entry->second->start - entry->second->lag;
	else
		return ticksSinceStart() - entry->second->start - entry->second->lag;
}

long TimeManager::getPausedTime(const std::string& tID)
{
	auto entry = timers.find(tID);

	if (entry == timers.end())
		return -1;

	if (entry->second->lag)
		return entry->second->lag;

	return 0;
}

long TimeManager::getPerfFreq()
{
	return SDL_GetPerformanceFrequency();
}

long TimeManager::ticksSinceStart()
{
	return SDL_GetTicks();
}

long TimeManager::perfSinceStart()
{
	return SDL_GetPerformanceCounter();
}

TimeManager* TimeManager::instance = nullptr;