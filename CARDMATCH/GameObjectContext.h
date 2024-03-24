#pragma once

#include <iostream>

#include "SDL.h"

#include "GameObjectState.h"

class GameObject;

class GameObjectContext : public Object
{
public:
    GameObjectContext(GameObject*, GameObjectState* = nullptr);
    ~GameObjectContext();

    void changeState(GameObjectState*);
    
    void update();
    void render();

private:
    GameObjectState* currentState;
    GameObject* object;
};