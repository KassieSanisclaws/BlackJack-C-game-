#pragma once

#include "SDL.h"

#include "GameEvent.h"

class InputHandler 
{
public:
    InputHandler();

    void setNextHandler(InputHandler*);

    virtual bool handleEvent(GameEvent*) = 0;

protected:
    InputHandler* nextHandler;
};
