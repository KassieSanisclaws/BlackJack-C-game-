#pragma once

#include <vector>

#include "SDL.h"

#include "GameEvent.h"
#include "Scene.h"

class GameObject;
class Scene;

class SceneManager
{
public:
	static SceneManager* getInstance();
	static void removeInstance();

	void update();
	void render();

	void addScene(Scene*);
	void changeScene(Scene*);
	void removeScene();

	Scene* getCurrentScene();

	void onUserEvent(GameEvent*);

	void onKeyDown(GameEvent*);
	void onKeyUp(GameEvent*);

	void onMouseButtonUp(GameEvent*);
	void onMouseButtonDown(GameEvent*);
	void onMouseMove(GameEvent*);

	void onControllerButtonDown(GameEvent*);
	void onControllerButtonUp(GameEvent*);
	void onControllerAxisMotion(GameEvent*);

private:
	SceneManager() = default;
	~SceneManager();

	std::vector<Scene*> gameStates;

	static SceneManager* instance;
};