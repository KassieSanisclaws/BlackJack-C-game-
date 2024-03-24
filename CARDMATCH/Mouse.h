#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

#include "SDL.h"

#include "SceneManager.h"
#include "GameEvent.h"
#include "MouseEvent.h"

class MouseInputHandler;
class InputManager;

typedef enum mouse_buttons
{
    MOUSELEFTBUTTON = SDL_BUTTON_LEFT,
    MOUSEMIDDLEBUTTON = SDL_BUTTON_MIDDLE,
    MOUSERIGHTBUTTON = SDL_BUTTON_RIGHT
} MOUSE_BUTTONS;

class Mouse
{
    friend class MouseInputHandler;
    friend class InputManager;

public:
    Mouse();

    void updateButtonState(Uint8, bool);

    bool getMouseButtonState(Uint8);
    const Vector2D& getMousePosition();

    void onMouseMove(GameEvent*);
    void onMouseButtonDown(GameEvent*);
    void onMouseButtonUp(GameEvent*);

    bool isMouseButtonPressed(Uint8);
    bool isMouseButtonDown(GameEvent*, Uint8);
    bool isMouseButtonUp(GameEvent*, Uint8);

    void setOnMouseButtonDown(Uint8 scancode, std::function<void()> action);
    void setOnMouseButtonUp(Uint8 scancode, std::function<void()> action);

    static Vector2D position;

private:
    static bool enabled;

    std::unordered_map<Uint8, bool> buttonStates;
    std::unordered_map<Uint8, std::function<void()>> onMouseButtonDownActions;
    std::unordered_map<Uint8, std::function<void()>> onMouseButtonUpActions;
};

