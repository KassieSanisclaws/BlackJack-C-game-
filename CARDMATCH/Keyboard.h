#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "GameEvent.h"
#include "KeyboardEvent.h"
#include "Key.h"

class KeyboardInputHandler;
class InputManager;

class Keyboard 
{
    friend class InputManager;
    friend class KeyboardInputHandler;

public:
    void updateKeyState(Key::Code, bool);
    
    void onKeyDown(GameEvent*);
    void onKeyUp(GameEvent*);

    bool isKeyPressed(Key::Code);
    bool isKeyDown(GameEvent*, Key::Code);
    bool isKeyUp(GameEvent*, Key::Code);

    void setOnKeyDown(Key::Code, std::function<void()> action);
    void setOnKeyUp(Key::Code, std::function<void()> action);

private:
    static bool enabled;

    std::unordered_map<Key::Code, bool> keyStates;
    std::unordered_map<Key::Code, std::function<void()>> onKeyDownActions;
    std::unordered_map<Key::Code, std::function<void()>> onKeyUpActions;
};

