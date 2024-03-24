#pragma once

#include "InputHandler.h"
#include "GameEvent.h"
#include "ControllerEvent.h"
#include "Controller.h"

class ControllerInputHandler : public InputHandler
{
public:
    bool handleEvent(GameEvent*);

private:
    Controller controller;
};