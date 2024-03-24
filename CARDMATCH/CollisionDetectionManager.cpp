#include "CollisionDetectionManager.h"
#include "GameObject.h"
#include "Collider.h"

CollisionDetectionManager::CollisionDetectionManager()
{

}

CollisionDetectionManager::~CollisionDetectionManager()
{
    auto it = gameObjects.begin();

    while (it != gameObjects.end())
    {
        delete* it;
        ++it;
    }
}

void CollisionDetectionManager::addCollider(GameObject* obj)
{
    gameObjects.push_back(obj);
}

void CollisionDetectionManager::visit(GameObject& wall)
{
    
}