#include "TextComponent.h"
#include "ResourceManager.h"

TextComponent::TextComponent()
	: position{ 0, 0 }, visible(true), filename(""), fontID(""), text(""), size(0), color{255, 255, 255, 255}
{

}

void TextComponent::loadAsset(std::string gameObjectID)
{
	font = ResourceManager::getInstance()->loadFont(gameObjectID, filename, size);
	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	w = surface->w;
	h = surface->h;

	SDL_FreeSurface(surface);

	if (font)
		fontID = gameObjectID;
}

TextComponent::~TextComponent()
{
	ResourceManager::getInstance()->removeFont(filename);
}