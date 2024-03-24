#include "InputHandler.h"

InputHandler::InputHandler() : nextHandler(nullptr)
{ }

void InputHandler::setNextHandler(InputHandler* handler)
{
    nextHandler = handler;
}