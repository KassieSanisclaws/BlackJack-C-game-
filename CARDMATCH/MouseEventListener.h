#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "EventListener.h"

class MouseEventListener : public EventListener
{
public:
    MouseEventListener(SDL_EventType, std::function<void(SDL_Event&)>);

    void onMouseButtonDown(SDL_Event&);
    void onMouseButtonUp(SDL_Event&);

private:
    std::function<void(SDL_Event&)> onMouseButtonDownActions;
    std::function<void(SDL_Event&)> onMouseButtonUpActions;
};