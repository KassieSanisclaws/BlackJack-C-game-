#pragma once

#include "Object.h"
#include "Vector2D.h"

class Collider;

class PhysicsComponent : public Object
{
public:
    PhysicsComponent();
    ~PhysicsComponent();

    Collider* collider;

    Vector2D velocity;
    Vector2D acceleration;

    long startTime;
    long endTime;

private:
    
};