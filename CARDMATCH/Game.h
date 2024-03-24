#pragma once

#include "Engine.h"

class Engine;

class Game
{
public:
	~Game();

	static Game* getInstance();
	static void removeInstance();
	
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

private:
	Game();

	Engine* engine;

	static Game* instance;
};