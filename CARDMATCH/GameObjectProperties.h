#pragma once

#include "Object.h"
#include "GraphicsComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "TextComponent.h"
#include "MusicComponent.h"
#include "SFXComponent.h"

class GameObjectProperties : public Object
{
public:
    GameObjectProperties();
    GameObjectProperties(GraphicsComponent* g = nullptr, AnimationComponent* a = nullptr, PhysicsComponent* p = nullptr, TextComponent* tc = nullptr, MusicComponent* mc = nullptr, SFXComponent* sfxc = nullptr);
    GameObjectProperties(const GameObjectProperties& properties);

    ~GameObjectProperties();

    GraphicsComponent* graphicsComponent;
    AnimationComponent* animationComponent;
    PhysicsComponent* physicsComponent;
    TextComponent* textComponent;
    MusicComponent* musicComponent;
    SFXComponent* sfxComponent;
    
private:

};