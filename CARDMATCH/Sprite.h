#pragma once

#include <iostream>
#include <string>

#include "GameObject.h"

class GameObject;
class GameObjectProperties;
class ResourceManager;
class AnimationManager;
class TimeManager;

class Sprite : public GameObject
{
public:
    Sprite();
    Sprite(std::string goID, std::string filename, float x, float y, int w, int h, int rows, int cols);
    Sprite(GameObjectProperties* properties);
    Sprite(const Sprite& other);

    virtual ~Sprite();

    virtual void update();
    virtual void render();

    Sprite* clone();
    void accept(GameObjectVisitor&);

    void addAnimation(std::string, const std::vector<int>);

    void play(int, int, int, bool = true, bool = false, bool = SDL_FLIP_NONE);
    void play(std::string, int, bool = true, bool = false, bool = SDL_FLIP_NONE);
    void stop();

    Collider* getCollider();
    bool checkCollision(Collider* b);

    void setCurrentFrame(int);
    int getCurrentFrame();
    SDL_Texture* getFrame();

    bool isAnimating();
    std::string getCurrentAnimation();

    bool isVisible();

    std::string getFilename();
    Vector2D getPosition();
    int getWidth();
    int getHeight();
    double getAngle();
    SDL_Rect getRect();
    
    void setPosition(Vector2D v);
    void setAngle(double);  
    void setEndTime(long);
    void setVisible(bool);

    void loadAsset(std::string goID);

    long getCurrentTime();
    long getStartTime();
    long getEndTime();
    float getDelta();

protected:
    ResourceManager* resourceManager;
    AnimationManager* animationManager;
    TimeManager* timeManager;
};