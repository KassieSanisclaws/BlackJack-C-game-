#include "Engine.h"
#include "Window.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "GameSettings.h"
#include "FrameGameLoop.h"
#include "FixedStepGameLoop.h"
#include "VariableStepGameLoop.h"
#include "ConfigurationManager.h"

Engine::~Engine()
{
	SceneManager::removeInstance();
	ResourceManager::removeInstance();
	InputManager::removeInstance();
	TimeManager::removeInstance();
	Window::removeInstance();

	SDL_Quit();
}

void Engine::init(int x, int y)
{
	srand(static_cast<unsigned>(time(0)));

	GameSettings* settings = GameSettings::getInstance();

	configManager = new ConfigurationManager("config/config.json");

	window = Window::getInstance(settings->title, x, y, settings->SCREEN_WIDTH, settings->SCREEN_HEIGHT, settings->renderer, settings->fullscreen);
	inputManager = InputManager::getInstance();
	sceneManager = SceneManager::getInstance();
	timeManager = TimeManager::getInstance();

	if (settings->gameloop == "variable")
	{
		std::cout << "Starting variable step gameloop..." << std::endl;
		gameloop = new VariableStepGameLoop();
	}
	else if (settings->gameloop == "fixed")
	{
		gameloop = new FixedStepGameLoop();
		std::cout << "Starting fixed step gameloop..." << std::endl;
	}
	else if (settings->gameloop == "frame")
	{
		gameloop = new FrameGameLoop();
		std::cout << "Starting frame based gameloop..." << std::endl;
	}
	else
	{
		gameloop = nullptr;
		std::cout << "Error: gameloop cannot be started..." << std::endl;
	}
}

// Update events
void Engine::handleEvents()
{
	gameloop->handleEvents();
}

void Engine::update()
{
	gameloop->update();
}

void Engine::render()
{
	gameloop->render();
}

void Engine::start()
{
	gameloop->process();
}

void Engine::stop()
{
	gameloop->running = !timeManager->remove("game");
}

void Engine::pause()
{
	gameloop->paused = timeManager->pause("game");
}

void Engine::resume()
{
	gameloop->paused = !timeManager->resume("game");;
}

void Engine::shutdown()
{
	if (isRunning())
		stop();
}

bool Engine::isRunning()
{
	return gameloop->running;
}

bool Engine::isPaused()
{
	return gameloop->paused;
}

SDL_Window* Engine::getWindow()
{
	return Window::getWindow();
}

SDL_Renderer* Engine::getRenderer()
{
	return Window::renderer;
}

TimeManager* Engine::getTimeManager()
{
	return TimeManager::getInstance();
}

long Engine::getStartTime()
{
	return gameloop->getStartTime();
}

float Engine::getDeltaTime()
{
	return gameloop->getDeltaTime();
}