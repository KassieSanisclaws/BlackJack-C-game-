#include "GameObjectContext.h"

GameObjectContext::GameObjectContext(GameObject* o, GameObjectState* s) : object(o), currentState(s)
{
    if(currentState)
        currentState->attachGameObject(object);
}

GameObjectContext::~GameObjectContext() 
{ 
 
}

void GameObjectContext::changeState(GameObjectState* newState)
{
    currentState = newState;
    currentState->attachGameObject(object);
}

void GameObjectContext::update() 
{
    currentState->update();
}

void GameObjectContext::render() 
{
    currentState->render();
}