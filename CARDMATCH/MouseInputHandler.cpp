#include "MouseInputHandler.h"
#include "InputManager.h"

bool MouseInputHandler::handleEvent(GameEvent* event)
{
	if (mouse.enabled)
	{
		MouseEvent* e = dynamic_cast<MouseEvent*>(event);

		if (e != nullptr)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				mouse.onMouseButtonDown(e);

				if (mouse.onMouseButtonDownActions.find(e->button) != mouse.onMouseButtonDownActions.end())
					mouse.onMouseButtonDownActions[e->button]();

				return true;
			}
			else if (e->type == SDL_MOUSEBUTTONUP)
			{
				mouse.onMouseButtonUp(e);

				if (mouse.onMouseButtonUpActions.find(e->button) != mouse.onMouseButtonUpActions.end())
					mouse.onMouseButtonUpActions[e->button]();

				return true;
			}
			else if (e->type == SDL_MOUSEMOTION)
			{
				mouse.onMouseMove(e);

				return true;
			}
		}
		else if (nextHandler != nullptr)
		{
			return nextHandler->handleEvent(event);
		}
	}

    return false;
}