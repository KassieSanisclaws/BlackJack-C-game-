#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "ControllerEvent.h"
#include "Vector2D.h"

class ControllerInputHandler;

typedef enum controller_button_state
{
	INVALID = SDL_CONTROLLER_BUTTON_INVALID,
	A = SDL_CONTROLLER_BUTTON_A,
	B = SDL_CONTROLLER_BUTTON_B,
	X = SDL_CONTROLLER_BUTTON_X,
	Y = SDL_CONTROLLER_BUTTON_Y,
	BACK = SDL_CONTROLLER_BUTTON_BACK,
	GUIDE = SDL_CONTROLLER_BUTTON_GUIDE,
	START = SDL_CONTROLLER_BUTTON_START,
	LEFTSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK,
	RIGHTSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
	LEFTSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
	RIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
	DPADUP = SDL_CONTROLLER_BUTTON_DPAD_UP,
	DPADDOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	DPADLEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	DPADRIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	MISC1 = SDL_CONTROLLER_BUTTON_MISC1,
	PADDLE1 = SDL_CONTROLLER_BUTTON_PADDLE1,
	PADDLE2 = SDL_CONTROLLER_BUTTON_PADDLE2,
	PADDLE3 = SDL_CONTROLLER_BUTTON_PADDLE3,
	PADDLE4 = SDL_CONTROLLER_BUTTON_PADDLE4,
	TOUCHPAD = SDL_CONTROLLER_BUTTON_TOUCHPAD,
	MAX = SDL_CONTROLLER_BUTTON_MAX
} CONTROLLER_BUTTON_STATE;

typedef enum controller_axis_state
{
	LEFTX = 0,
	LEFTY = 1,
	RIGHTX = 2,
	RIGHTY = 3,
	TRIGGERLEFT = 4,
	TRIGGERRIGHT = 5
} CONTROLLER_AXIS_STATE;

typedef struct controlleraxis
{
	int xAxis;
	int yAxis;
	int xDirection;
	int yDirection;
	double angle;
} ControllerAxis;

class Controller
{
	friend class ControllerInputHandler;

public:
    Controller();
	~Controller();

	void init(SDL_Event&);
	void removeController(SDL_Event&);

	void updateButtonState(Uint8, bool);

	bool getControllerAxisStates(Uint8);

	void onControllerButtonDown(ControllerEvent*);
	void onControllerButtonUp(ControllerEvent*);
	void onControllerAxisMotion(ControllerEvent*);

	bool isButtonPressed(Uint8);
	bool isButtonDown(SDL_Event&, Uint8);
	bool isButtonUp(SDL_Event&, Uint8);
	
	void setOnButtonDown(Uint8, std::function<void()>);
	void setOnButtonUp(Uint8, std::function<void()>);

	std::unordered_map<int, SDL_GameController*> controllers;
	std::vector<ControllerAxis> controllerAxis;
	std::vector<bool> controllerAxisStates;

	static int numControllers;

    Vector2D position;

	static const int JOYSTICK_DEADZONE;

	std::unordered_map<Uint8, bool> buttonStates;
	std::unordered_map<Uint8, std::function<void()>> onButtonDownActions;
	std::unordered_map<Uint8, std::function<void()>> onButtonUpActions;
};