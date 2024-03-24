#include "Game.h"

Game::Game()
{
	engine = new Engine();
}

Game::~Game()
{	
	delete engine;
}

Game* Game::getInstance()
{
	if (instance == nullptr)
		instance = new Game();

	return instance;
}

void Game::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void Game::init(int x, int y)
{
	engine->init(x, y);
}

void Game::start()
{
	engine->start();
}

void Game::stop()
{
	engine->stop();
}

void Game::pause()
{
	engine->pause();
}

void Game::resume()
{
	engine->resume();
}

void Game::shutdown()
{
	engine->shutdown();

	if (instance != nullptr)
		Game::removeInstance();
}

bool Game::isRunning()
{
	return engine->isRunning();
}

bool Game::isPaused()
{
	return engine->isPaused();
}

long Game::getStartTime()
{
	return engine->getStartTime();
}

float Game::getDeltaTime()
{
	return engine->getDeltaTime();
}

Game* Game::instance = nullptr;