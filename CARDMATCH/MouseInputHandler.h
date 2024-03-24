#pragma once

#include "InputHandler.h"
#include "GameEvent.h"
#include "Mouse.h"

class MouseInputHandler : public InputHandler 
{
public:
    bool handleEvent(GameEvent*);

private:
    Mouse mouse;
};
