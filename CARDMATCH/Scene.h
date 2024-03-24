#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "SDL.h"

#include "GameObject.h"
#include "MusicComponent.h"
#include "GameEvent.h"

class GameObject;

class Scene : public GameObject
{
public:
	Scene(const Scene&);
	virtual ~Scene();

	Scene* clone();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void onUserEvent(GameEvent*) { }

	virtual void onKeyDown(GameEvent*) { }
	virtual void onKeyUp(GameEvent*) { }

	virtual void onMouseButtonDown(GameEvent*) { }
	virtual void onMouseButtonUp(GameEvent*) { }
	virtual void onMouseMove(GameEvent*) { }

	virtual void onControllerButtonDown(GameEvent*) { }
	virtual void onControllerButtonUp(GameEvent*) { }
	virtual void onControllerAxisMotion(GameEvent*) { }

	std::string getSceneID() const;

	void addGameObject(GameObject*, int);
	void removeGameObject(GameObject*);
	GameObject* getObjectByID(std::string);

	void addMusic(std::string);
	void playMusic();

	int gameObjectSize;
	std::unordered_map<std::string, int> depthMap;
	std::unordered_map<std::string, GameObject*> gameObjectMap;

protected:
	Scene(std::string="");

	MusicComponent* mc;

	std::string sceneID;
};