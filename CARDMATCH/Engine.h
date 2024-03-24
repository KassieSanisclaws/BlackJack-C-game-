#pragma once

#include <cstdlib>
#include <ctime>

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

class Window;
class InputManager;
class SceneManager;
class TimeManager;
class ResourceManager;
class Game;
class GameLoop;
class ConfigurationManager;

class Engine
{
	friend class Game;

public:
	Engine() = default;
	~Engine();

	void init(int, int);

	void start();
	void stop();
	void pause();
	void resume();
	void shutdown();

	bool isRunning();
	bool isPaused();

	long getStartTime();
	float getDeltaTime();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	TimeManager* getTimeManager();

private:
	void handleEvents();
	void update();
	void render();

	Window* window;
	InputManager* inputManager;
	SceneManager* sceneManager;
	TimeManager* timeManager;
	ConfigurationManager* configManager;
	GameLoop* gameloop;
};