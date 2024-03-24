#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "EventListener.h"

class ControllerEventListener : public EventListener
{
public:
    ControllerEventListener(SDL_EventType, std::function<void(SDL_Event&)>);

    void onControllerButtonDown(SDL_Event&);
    void onControllerButtonUp(SDL_Event&);

private:
    std::function<void(SDL_Event&)> onControllerButtonDownActions;
    std::function<void(SDL_Event&)> onControllerButtonUpActions;
};
