#pragma once

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Object.h"
#include "Vector2D.h"

class ResourceManager;

class TextComponent : public Object
{
public:
	TextComponent();
	~TextComponent();

	void loadAsset(std::string gameObjectID);

	bool visible;

	Vector2D position;
	int size;
	int w;
	int h;

	std::string text;
	SDL_Color color;

	std::string filename;

private:
	std::string fontID;
	TTF_Font* font;
};
