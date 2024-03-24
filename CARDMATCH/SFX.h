#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "GameObject.h"

class ResourceManager;

class SFX : public GameObject
{
public:
    SFX();
    SFX(std::string goID, std::string filename);
    SFX(GameObjectProperties* properties);
    SFX(const SFX& other);

    virtual ~SFX();

    virtual void update();
    virtual void render();

    SFX* clone();
    void accept(GameObjectVisitor&);

    void addSFX(std::string goID, std::string filename);

    void play(std::string);

protected:
    ResourceManager* resourceManager;
    static std::unordered_map<std::string, SFXComponent*> library;
};