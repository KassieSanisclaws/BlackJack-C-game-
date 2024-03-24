#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "EventListener.h"

class KeyboardEventListener : public EventListener 
{
public:
    KeyboardEventListener(SDL_EventType, std::function<void(SDL_Event&)>);

    void onKeyDown(SDL_Event&);
    void onKeyUp(SDL_Event&);

private:
    std::function<void(SDL_Event&)> onKeyDownActions;
    std::function<void(SDL_Event&)> onKeyUpActions;
};