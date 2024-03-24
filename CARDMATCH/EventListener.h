#pragma once

#include "SDL.h"

#include "GameEvent.h"

class EventListener
{
public:
    virtual void onKeyDown(GameEvent&) { };
    virtual void onKeyUp(GameEvent&) { };
    virtual void onMouseButtonUp(GameEvent&) { };
    virtual void onMouseButtonDown(GameEvent&) { };
    virtual void onControllerButtonDown(GameEvent&) { };
    virtual void onControllerButtonUp(GameEvent&) { };
};