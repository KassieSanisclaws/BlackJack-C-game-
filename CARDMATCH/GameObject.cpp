#include "GameObject.h"

GameObject::GameObject()
    : properties(nullptr), context(nullptr)
{ }

GameObject::GameObject(GraphicsComponent* g, AnimationComponent* a, PhysicsComponent* p, TextComponent* tc, MusicComponent* mc, SFXComponent* sfxc)
    : properties{ new GameObjectProperties(g, a, p, tc, mc, sfxc) }, context(nullptr)
{ }

GameObject::GameObject(GameObjectProperties* gop)
    : properties(gop), context(nullptr)
{ }

GameObject::~GameObject()
{
    if (properties != nullptr)
        delete properties;

    properties = nullptr;

    if (context != nullptr)
    {
        delete context;
        context = nullptr;
    }
}

std::string GameObject::getGameObjectID()
{
    return gameObjectID;
}

void GameObject::setGameObjectID(std::string goID)
{
    gameObjectID = goID;
}

void GameObject::update()
{
    context->update();
}

void GameObject::render()
{
    context->render();
}

void GameObject::addContext(GameObjectContext* c)
{
    context = c;
}

void GameObject::changeState(GameObjectState* s)
{
    context->changeState(s);
}