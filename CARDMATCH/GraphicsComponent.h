#pragma once

#include <string>

#include "SDL.h"

#include "Object.h"
#include "Vector2D.h"

class ResourceManager;

class GraphicsComponent : public Object
{
public:
	GraphicsComponent();
	~GraphicsComponent();

	void loadAsset(std::string gameObjectID);

	Vector2D position;
	double angle;
	int w;
	int h;
	int rows;
	int cols;
	int offsetX;
	int offsetY;

	SDL_RendererFlip orientation;

	bool visible;

	std::string filename;
	SDL_Texture* texture;
};