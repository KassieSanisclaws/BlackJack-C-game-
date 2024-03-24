#pragma once

#include <string>

#include "rapidjson/document.h"

#include "GameObjectSettings.h"

class GameObject;

class GameObjectFactory 
{
public:
    static GameObject* createGameObject(const GameObjectSettings&);
};