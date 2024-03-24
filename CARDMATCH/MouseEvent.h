#pragma once

#include "GameEvent.h"
#include "Vector2D.h"

class MouseEvent : public GameEvent
{
public:
	MouseEvent(SDL_Event&);

	Uint32 timestamp;
	Uint32 button;
	Uint32 buttonState;
	Uint8 numClicks;
	
	Vector2D position;
};