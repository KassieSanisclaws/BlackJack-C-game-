#include "GameLoop.h"
#include "Window.h"
#include "InputManager.h"

void GameLoop::handleEvents()
{
	InputManager::getInstance()->handleEvents();
}

void GameLoop::update()
{
	if (!isPaused())
		Window::update();
}

void GameLoop::render()
{
	if (!isPaused())
		Window::render();
}

bool GameLoop::isRunning()
{
	return running;
}

bool GameLoop::isPaused()
{
	return paused;
}

long GameLoop::getStartTime()
{
	return startTime;
}

float GameLoop::getDeltaTime()
{
	return delta;
}

const float GameLoop::FPS = 60.0f;
const float GameLoop::DELAY_TIME = 1000.0f / FPS;