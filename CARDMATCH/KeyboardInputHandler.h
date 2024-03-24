#pragma once

#include "InputHandler.h"
#include "GameEvent.h"
#include "Keyboard.h"

class KeyboardInputHandler : public InputHandler 
{
public:
    bool handleEvent(GameEvent*);

private:
    Keyboard keyboard;
};