#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Game.h"
#include "Scene.h"
#include "Image.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "GameEvent.h"
#include "GameSettings.h"

#include "Card.h"
#include "Deck.h"
#include "Selector.h"

class PlayScene : public Scene
{
public:
	PlayScene(std::string);
	~PlayScene() = default;

	void update();
	void render();

	bool onEnter();
	bool onExit();

	virtual void onUserEvent(GameEvent*);

	virtual void onKeyDown(GameEvent*);
	virtual void onKeyUp(GameEvent*);

	virtual void onMouseButtonDown(GameEvent*);
	virtual void onMouseButtonUp(GameEvent*);
	virtual void onMouseMove(GameEvent*);

	virtual void onControllerButtonDown(GameEvent*);
	virtual void onControllerButtonUp(GameEvent*);
	virtual void onControllerAxisMotion(GameEvent*);

private:
	Image* bg;
	Image* logo;
	Image* button;
	
	static Game* game;
};