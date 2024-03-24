#pragma once

class GameObject;

class GameObjectVisitor 
{
public:
    virtual void visit(GameObject&) = 0;
};