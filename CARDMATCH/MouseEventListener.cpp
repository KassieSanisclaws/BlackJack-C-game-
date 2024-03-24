#include "MouseEventListener.h"

MouseEventListener::MouseEventListener(SDL_EventType type, std::function<void(SDL_Event&)> a)
{
    onMouseButtonDownActions = nullptr;
    onMouseButtonUpActions = nullptr;

    if (type == SDL_MOUSEBUTTONDOWN)
        onMouseButtonDownActions = a;
    else if (type == SDL_MOUSEBUTTONUP)
        onMouseButtonUpActions = a;
}

void MouseEventListener::onMouseButtonDown(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
        if (onMouseButtonDownActions)
            onMouseButtonDownActions(e);
}

void MouseEventListener::onMouseButtonUp(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONUP)
        if (onMouseButtonUpActions)
            onMouseButtonUpActions(e);
}