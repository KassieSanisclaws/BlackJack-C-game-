#include "VariableStepGameLoop.h"
#include "TimeManager.h"

VariableStepGameLoop::VariableStepGameLoop()
{
	running = TimeManager::getInstance()->addTimer("game", false);
	startTime = TimeManager::getInstance()->get("game");
    currentTime = startTime;
    previousTime = startTime;
    delta = DELAY_TIME;
    lag = 0;
    paused = false;
}

void VariableStepGameLoop::process()
{
    while (isRunning()) 
    {
        currentTime = TimeManager::getInstance()->get("game");
        lag += currentTime - previousTime;
        previousTime = currentTime;

        handleEvents();

        while (lag >= DELAY_TIME) 
        {
            update();
            lag -= DELAY_TIME;
        }

        render();
    }
}