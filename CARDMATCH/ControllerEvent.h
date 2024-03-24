#pragma once

#include "GameEvent.h"
#include "Vector2D.h"

class ControllerEvent : public GameEvent
{
public:
	ControllerEvent(SDL_Event&);

	SDL_JoystickID id;
	Uint32 timestamp;
	Uint8 button;
	Uint8 state;
	Uint8 axis;
	Sint16 axisValue;
};