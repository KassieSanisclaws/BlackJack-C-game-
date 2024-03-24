#include "ControllerInputHandler.h"

bool ControllerInputHandler::handleEvent(GameEvent* event)
{
    ControllerEvent* e = dynamic_cast<ControllerEvent*>(event);

    if (e != nullptr)
    {
        if (e->type == SDL_CONTROLLERBUTTONDOWN)
        {
            controller.updateButtonState(e->button, true);

            controller.onControllerButtonDown(e);

            if (controller.onButtonDownActions.find(e->button) != controller.onButtonDownActions.end())
            {
                controller.onButtonDownActions[e->button]();
            }

            return true;
        }
        else if (e->type == SDL_CONTROLLERBUTTONUP)
        {
            controller.updateButtonState(e->button, false);

            controller.onControllerButtonUp(e);

            if (controller.onButtonUpActions.find(e->button) != controller.onButtonUpActions.end())
            {
                controller.onButtonUpActions[e->button]();
            }

            return true;
        }
        else if (e->type == SDL_CONTROLLERAXISMOTION)
        {
            controller.onControllerAxisMotion(e);

            return true;
        }
    }
    else if (nextHandler != nullptr)
    {
        return nextHandler->handleEvent(event);
    }

    return false;
}