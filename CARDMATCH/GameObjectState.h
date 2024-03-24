#pragma once

#include "SDL.h"

#include "Object.h"

class GameObject;

class GameObjectState : public Object
{
public:
    virtual ~GameObjectState() = default;

    void attachGameObject(GameObject*);

    virtual void update() = 0;
    virtual void render() = 0;

protected:
    GameObject* object;
};

