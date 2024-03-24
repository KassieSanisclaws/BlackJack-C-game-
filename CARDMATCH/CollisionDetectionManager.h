#pragma once

#include <vector>

#include "GameObjectVisitor.h"

class GameObject;

class CollisionDetectionManager : public GameObjectVisitor 
{
public:
    CollisionDetectionManager();
    ~CollisionDetectionManager();

    void addCollider(GameObject*);

    void visit(GameObject&);

    std::vector<GameObject*> gameObjects;
};
