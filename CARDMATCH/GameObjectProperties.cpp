#include "GameObjectProperties.h"

GameObjectProperties::GameObjectProperties() 
    : graphicsComponent(nullptr), animationComponent(nullptr), physicsComponent(nullptr), textComponent(nullptr), musicComponent(nullptr), sfxComponent(nullptr)
{ }

GameObjectProperties::GameObjectProperties(GraphicsComponent* g, AnimationComponent* a, PhysicsComponent* p, TextComponent* t, MusicComponent* mc, SFXComponent* sfxc)
    : graphicsComponent(g), animationComponent(a), physicsComponent(p), textComponent(t), musicComponent(mc), sfxComponent(sfxc)
{ }

GameObjectProperties::GameObjectProperties(const GameObjectProperties& properties) 
    : graphicsComponent(properties.graphicsComponent), animationComponent(properties.animationComponent), physicsComponent(properties.physicsComponent), textComponent(properties.textComponent), musicComponent(properties.musicComponent), sfxComponent(properties.sfxComponent)
{ }

GameObjectProperties::~GameObjectProperties()
{
    if (graphicsComponent != nullptr)
        delete graphicsComponent;
    if (animationComponent != nullptr)
        delete animationComponent;
    if (physicsComponent != nullptr)
        delete physicsComponent;
    if (textComponent != nullptr)
        delete textComponent;
    if (musicComponent != nullptr)
        delete musicComponent;
    if (sfxComponent != nullptr)
        delete sfxComponent;

    graphicsComponent = nullptr;
    animationComponent = nullptr;
    physicsComponent = nullptr;
    textComponent = nullptr;
    musicComponent = nullptr;
    sfxComponent = nullptr;
}