#pragma once

#include <string>

#include "SDL.h"

#include "GameObject.h"
#include "Vector2D.h"
#include "ResourceManager.h"

class GameObjectProperties;
class GameObject;
class ResourceManager;

class Text : public GameObject
{
public:
    Text();
    Text(std::string goID, std::string filename, std::string text, float x, float y, int, SDL_Color = { 0, 0, 0, 255 });
    Text(GameObjectProperties* properties);
    Text(const Text& other);

    virtual ~Text();

    virtual void update();
    virtual void render();

    Text* clone();
    void accept(GameObjectVisitor&);

    bool isVisible();

    std::string getFilename();
    Vector2D getPosition();
    std::string getText();
    int getSize();
    int getWidth();
    int getHeight();
    SDL_Rect getRect();
    SDL_Color getColor();

    void setPosition(Vector2D v);
    void setText(std::string);
    void setSize(int);
    void setVisible(bool);
    void setColor(SDL_Color);
    void setColor(Uint8, Uint8, Uint8, Uint8);

    void loadAsset(std::string goID);

    std::string text;
};