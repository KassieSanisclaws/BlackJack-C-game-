#include "KeyboardEventListener.h"

KeyboardEventListener::KeyboardEventListener(SDL_EventType type, std::function<void(SDL_Event&)> a)
{
    onKeyDownActions = nullptr;
    onKeyUpActions = nullptr;

    onKeyDownActions = a;
}

void KeyboardEventListener::onKeyDown(SDL_Event& e)
{
    if(onKeyDownActions)
        onKeyDownActions(e);
}

void KeyboardEventListener::onKeyUp(SDL_Event& e)
{
    if(onKeyUpActions)
        onKeyUpActions(e);
}