#pragma once

#include <string>

#include "GameObject.h"
#include "Vector2D.h"

class GameObjectProperties;
class GameObject;
class ResourceManager;

class Image : public GameObject
{
public:
    Image();
    Image(std::string goID, std::string filename, float x, float y, int w, int h, int rows, int cols);
    Image(GameObjectProperties* properties);
    Image(const Image& other);

    virtual ~Image();

    virtual void update();
    virtual void render();

    Image* clone();
    void accept(GameObjectVisitor&);

    bool isVisible();

    std::string getFilename();
    Vector2D getPosition();
    int getWidth();
    int getHeight();
    double getAngle();
    SDL_Rect getRect();

    void setPosition(float x, float y);
    void setAngle(double);
    void setVisible(bool);

    void loadAsset(std::string goID);
};