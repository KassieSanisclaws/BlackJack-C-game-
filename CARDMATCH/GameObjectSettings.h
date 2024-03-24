#pragma once

#include <string>

#include "Vector2D.h"

class GameObjectSettings
{
public:
    GameObjectSettings();
    ~GameObjectSettings();

    GameObjectSettings& operator=(const GameObjectSettings&) = delete;

    std::string type;
    Vector2D position;
    int w;
    int h;

    int rows;
    int cols;

    std::string gameObjectID;
    std::string filename;

private:
    
};