#include "SceneManager.h"
#include "SceneSettings.h"

#include "GameObjectFactory.h"

SceneManager::~SceneManager()
{
	for (int i = 0; i < gameStates.size(); ++i)
	{
		if (gameStates[i]->onExit())
			delete gameStates[i];
	}
}

SceneManager* SceneManager::getInstance()
{
	if (instance == nullptr)
		instance = new SceneManager();

	return instance;
}

void SceneManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

void SceneManager::addScene(Scene* state)
{
	gameStates.push_back(state);

	if (state->getSceneID() == SceneSettings::getInstance()->sceneID)
	{
		if (!SceneSettings::getInstance()->objects.empty())
		{
			auto it = SceneSettings::getInstance()->objects.begin();

			while (it != SceneSettings::getInstance()->objects.end())
			{
				auto obj = GameObjectFactory::createGameObject((*it));

				state->addGameObject(obj, state->gameObjectSize);

				it++;
			}
		}
	}

	gameStates.back()->onEnter();
}

void SceneManager::changeScene(Scene* state)
{
	if (!gameStates.empty())
			return;

	gameStates.push_back(state);

	if (!gameStates.empty())
		if (gameStates.back()->onExit())
			gameStates.erase(gameStates.end() - 2);

	gameStates.back()->onEnter();
}

void SceneManager::removeScene()
{
	if (!gameStates.empty())
		if (gameStates.back()->onExit())
			gameStates.erase(gameStates.end() - 1);
}

Scene* SceneManager::getCurrentScene()
{
	return gameStates.back();
}

void SceneManager::update()
{
	if (!gameStates.empty())
		gameStates.back()->update();
}

void SceneManager::render()
{
	if (!gameStates.empty())
		gameStates.back()->render();
}

void SceneManager::onKeyDown(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onKeyDown(e);
}

void SceneManager::onKeyUp(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onKeyUp(e);
}

void SceneManager::onUserEvent(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onUserEvent(e);
}

void SceneManager::onMouseButtonDown(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseButtonDown(e);
}

void SceneManager::onMouseButtonUp(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseButtonUp(e);
}

void SceneManager::onMouseMove(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onMouseMove(e);
}

void SceneManager::onControllerButtonDown(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerButtonDown(e);
}

void SceneManager::onControllerButtonUp(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerButtonUp(e);
}

void SceneManager::onControllerAxisMotion(GameEvent* e)
{
	if (!gameStates.empty())
		gameStates.back()->onControllerAxisMotion(e);
}

SceneManager* SceneManager::instance = nullptr;