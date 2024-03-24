#pragma once

#include "GameEvent.h"
#include "Vector2D.h"
#include "Key.h"

class KeyboardEvent : public GameEvent
{
public:
	KeyboardEvent(SDL_Event&);

	Uint32 timestamp;
	Uint32 state;
	Uint8 repeat;
	Key key;
};