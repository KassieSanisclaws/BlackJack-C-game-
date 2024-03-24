#pragma once

#include "SDL.h"

#include "Object.h"

class GameEvent : public Object
{
public:
	virtual ~GameEvent() = default;

	Uint32 type;
};