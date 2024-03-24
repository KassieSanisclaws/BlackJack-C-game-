#include "FixedStepGameLoop.h"
#include "TimeManager.h"

FixedStepGameLoop::FixedStepGameLoop()
{
	running = TimeManager::getInstance()->addTimer("game", false);
	startTime = TimeManager::getInstance()->get("game");
	currentTime = startTime;
	previousTime = startTime;
	delta = DELAY_TIME;
	paused = false;
}

void FixedStepGameLoop::process()
{
	while (isRunning())
	{
		currentTime = TimeManager::getInstance()->get("game");

		handleEvents();
		update();
		render();

		int elapsed = TimeManager::getInstance()->get("game") - currentTime;

		if (elapsed > 0 && elapsed < GameLoop::DELAY_TIME)
			SDL_Delay((GameLoop::DELAY_TIME - elapsed));
	}
}