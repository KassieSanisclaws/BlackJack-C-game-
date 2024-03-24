#include "FrameGameLoop.h"
#include "TimeManager.h"

FrameGameLoop::FrameGameLoop()
{
	running = TimeManager::getInstance()->addTimer("game", false);
	startTime = TimeManager::getInstance()->get("game");
	currentTime = startTime;
	previousTime = startTime;
	delta = DELAY_TIME;
	paused = false;
}

void FrameGameLoop::process()
{
	while (isRunning())
	{
		handleEvents();
		update();
		render();
	}
}