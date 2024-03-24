#pragma once

#include <string>

#include "Object.h"
#include "Vector2D.h"
#include "GameObjectProperties.h"
#include "GameObjectContext.h"

class GraphicsComponent;
class AnimationComponent;
class PhysicsComponent;
class TextComponent;
class MusicComponent;
class SFXComponent;
class GameObjectProperties;
class GameObjectState;
class GameObjectVisitor;

class GameObject : public Object
{
public:
    GameObject();
    GameObject(GraphicsComponent* g, AnimationComponent* a, PhysicsComponent* p, TextComponent* tc, MusicComponent* mc, SFXComponent* sfxc);
    GameObject(GameObjectProperties* gop);

    virtual ~GameObject();

    virtual void update() = 0;
    virtual void render() = 0;

    virtual GameObject* clone() = 0;
    virtual void accept(GameObjectVisitor&) { };

    std::string getGameObjectID();
    void setGameObjectID(std::string goID);

    void addContext(GameObjectContext*);
    void changeState(GameObjectState*);

    GameObjectProperties* properties;

    GameObjectContext* context;

protected:
    std::string gameObjectID;
};