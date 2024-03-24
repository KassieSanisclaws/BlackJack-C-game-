#include "GraphicsComponent.h"
#include "ResourceManager.h"

GraphicsComponent::GraphicsComponent() 
	: position(0.0f, 0.0f), angle(0.0), w(0), h(0), rows(1), cols(1), offsetX(0), offsetY(0), orientation(SDL_FLIP_NONE), visible(true), filename(""), texture(nullptr)
{ }

void GraphicsComponent::loadAsset(std::string gameObjectID)
{
	texture = ResourceManager::getInstance()->loadTexture(gameObjectID, filename, rows, cols, offsetX, offsetY);

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}

GraphicsComponent::~GraphicsComponent()
{
	SDL_DestroyTexture(texture);
}