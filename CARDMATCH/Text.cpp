#include "Text.h"
#include "Renderer.h"
#include "GameObjectVisitor.h"

Text::Text() : GameObject(nullptr)
{ }

Text::Text(std::string goID, std::string filename, std::string text, float x, float y, int size, SDL_Color color)
    : GameObject()
{
    GraphicsComponent* gc = nullptr;
    AnimationComponent* ac = nullptr;
    PhysicsComponent* pc = nullptr;
    TextComponent* tc = new TextComponent();

    properties = new GameObjectProperties(gc, ac, pc, tc);

    gameObjectID = goID;
    tc->filename = filename;
    tc->text = text;
    tc->position = { x, y };
    tc->size = size;
    tc->color = color;

    loadAsset(goID);
}

Text::Text(GameObjectProperties* properties)
    : GameObject(properties)
{ }

Text::Text(const Text& other)
{
    GraphicsComponent* gc = nullptr;
    AnimationComponent* ac = nullptr;
    PhysicsComponent* pc = nullptr;
    TextComponent* tc = new TextComponent();

    properties = new GameObjectProperties(gc, ac, pc, tc);
}

Text::~Text()
{ }

Text* Text::clone()
{
    return new Text(*this);
}

void Text::accept(GameObjectVisitor& visitor)
{

}

void Text::update()
{ }

void Text::render()
{
    TextComponent* tc = properties->textComponent;

    if (tc->visible)
    {
        TTF_Font* font = ResourceManager::getInstance()->findFont(getFilename());
        SDL_Surface* surface = TTF_RenderText_Solid(font, tc->text.c_str(), tc->color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::getRenderer(), surface);

        tc->w = surface->w;
        tc->h = surface->h;

        SDL_Rect dest = { static_cast<int>(tc->position.x), static_cast<int>(tc->position.y), tc->w, tc->h };

        SDL_RenderCopy(Renderer::getInstance()->getRenderer(), texture, nullptr, &dest);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

void Text::loadAsset(std::string goID)
{
    properties->textComponent->loadAsset(goID);
}

std::string Text::getFilename()
{
    return properties->textComponent->filename;
}

Vector2D Text::getPosition()
{
    return properties->textComponent->position;
}

std::string Text::getText()
{
    return properties->textComponent->text;
}

int Text::getSize()
{
    return properties->textComponent->size;
}

int Text::getWidth()
{
    return properties->textComponent->w;
}

int Text::getHeight()
{
    return properties->textComponent->h;
}

void Text::setPosition(Vector2D v)
{
    properties->textComponent->position = v;
}

void Text::setText(std::string t)
{
    properties->textComponent->text = t;
}

void Text::setSize(int size)
{
    properties->textComponent->size = size;
}

void Text::setColor(SDL_Color color)
{
    properties->textComponent->color = color;
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    properties->textComponent->color = { r, g, b, a };
}

SDL_Color Text::getColor()
{
    return properties->textComponent->color;
}

bool Text::isVisible()
{
    return properties->textComponent->visible;
}

void Text::setVisible(bool visible)
{
    properties->textComponent->visible = visible;
}