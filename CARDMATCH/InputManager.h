#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

#include "SDL.h"

#include "Game.h"
#include "SceneManager.h"
#include "Vector2D.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Key.h"

#include "KeyboardInputHandler.h"
#include "MouseInputHandler.h"
#include "ControllerInputHandler.h"

#include "GameEvent.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "ControllerEvent.h"

#include "EventListener.h"

struct Combo 
{
	std::vector<Key::Code> sequence;
	std::function<void()> action;
};

class InputManager
{
public:
	static InputManager* getInstance();
	static void removeInstance();

	void init();
	void handleEvents();
	void pollEvents();
	void processEvents();
	
	void addEventListener(EventListener*);
	void removeEventListener(EventListener*);
	void notify(GameEvent&);

	bool checkCombo();
	void addCombo(const Combo&);
	bool isCombo(const Combo&);

	void enableKeyboard();
	void disbaleKeyboard();
	void enableMouse();
	void disableMouse();

	void onUserEvent(GameEvent*);

	Keyboard keyboard;
	Mouse mouse;
	Controller controller;

	KeyboardInputHandler keyboardHandler;
	MouseInputHandler mouseHandler;
	ControllerInputHandler controllerHandler;

	std::deque<Key::Code> inputHistory;
	std::vector<Combo> combos;

private:
	InputManager();
	~InputManager();

	std::queue<GameEvent*> eventQueue;

	std::vector<EventListener*> observers;

	static InputManager* instance;
};