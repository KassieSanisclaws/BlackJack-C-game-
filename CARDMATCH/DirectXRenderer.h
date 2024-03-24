#pragma once

#include <iostream>

#include "SDL.h"

#include "RendererFactory.h"
#include "SceneManager.h"
#include "GameSettings.h"

class DirectXRenderer : public RendererFactory
{
public:
	DirectXRenderer(SDL_Window*);
	~DirectXRenderer();

	void init();

	void render();

private:
	SDL_Texture* backBuffer;
};