#include "ControllerEventListener.h"

ControllerEventListener::ControllerEventListener(SDL_EventType type, std::function<void(SDL_Event&)> a)
{
    onControllerButtonDownActions = nullptr;
    onControllerButtonUpActions = nullptr;

    onControllerButtonDownActions = a;
}

void ControllerEventListener::onControllerButtonDown(SDL_Event& e)
{
    if (onControllerButtonDownActions)
        onControllerButtonDownActions(e);
}

void ControllerEventListener::onControllerButtonUp(SDL_Event& e)
{
    if (onControllerButtonUpActions)
        onControllerButtonUpActions(e);
}