#include "Keyboard.h"
#include "SceneManager.h"

void Keyboard::updateKeyState(Key::Code scancode, bool isPressed)
{
    keyStates[scancode] = isPressed;
}

void Keyboard::onKeyDown(GameEvent* event)
{
    KeyboardEvent* e = dynamic_cast<KeyboardEvent*>(event);

    std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.sym) << std::endl;

    SceneManager::getInstance()->onKeyDown(e);
}

void Keyboard::onKeyUp(GameEvent* event)
{
    KeyboardEvent* e = dynamic_cast<KeyboardEvent*>(event);

    std::cout << "Key Released: " << SDL_GetKeyName(e->key.sym) << std::endl;

    SceneManager::getInstance()->onKeyUp(e);
}

bool Keyboard::isKeyPressed(Key::Code scancode)
{
    auto it = keyStates.find(scancode);

    return it != keyStates.end() && it->second;
}

bool Keyboard::isKeyDown(GameEvent* event, Key::Code key)
{
    KeyboardEvent* e = dynamic_cast<KeyboardEvent*>(event);

    return e->type == SDL_KEYDOWN && e->state == SDL_PRESSED && e->key.code == key;
}

bool Keyboard::isKeyUp(GameEvent* event, Key::Code key)
{
    KeyboardEvent* e = dynamic_cast<KeyboardEvent*>(event);

    return e->type == SDL_KEYUP && e->state == SDL_RELEASED && e->key.code == key;
}

void Keyboard::setOnKeyDown(Key::Code scancode, std::function<void()> action)
{
    onKeyDownActions[scancode] = action;
}

void Keyboard::setOnKeyUp(Key::Code scancode, std::function<void()> action)
{
    onKeyUpActions[scancode] = action;
}

bool Keyboard::enabled = true;