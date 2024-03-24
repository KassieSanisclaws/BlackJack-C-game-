#include "KeyboardInputHandler.h"

bool KeyboardInputHandler::handleEvent(GameEvent* event)
{
    if (keyboard.enabled)
    {
        KeyboardEvent* e = dynamic_cast<KeyboardEvent*>(event);

        if (e != nullptr)
        {
            if (e->type == SDL_KEYDOWN)
            {
                keyboard.updateKeyState(e->key.code, true);

                keyboard.onKeyDown(e);

                if (keyboard.onKeyDownActions.find(e->key.code) != keyboard.onKeyDownActions.end())
                    keyboard.onKeyDownActions[e->key.code]();

                return true;
            }
            else if (e->type == SDL_KEYUP)
            {
                keyboard.updateKeyState(e->key.code, false);

                keyboard.onKeyUp(e);

                if (keyboard.onKeyUpActions.find(e->key.code) != keyboard.onKeyUpActions.end())
                    keyboard.onKeyUpActions[e->key.code]();

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