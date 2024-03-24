#include "DirectXRenderer.h"

DirectXRenderer::DirectXRenderer(SDL_Window* w)
{
	window = w;

	renderer = nullptr;
}

DirectXRenderer::~DirectXRenderer()
{
	SDL_DestroyTexture(backBuffer);
}

void DirectXRenderer::init()
{
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer)
	{
		std::cout << "Renderer created..." << std::endl;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		backBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT);

		if (backBuffer == nullptr)
		{
			std::cout << "Error: Could not create back buffer" << std::endl;
		}
	}
	else
		std::cout << "Error: Renderer was not created" << std::endl;
}

void DirectXRenderer::render()
{
	if (renderer)
	{
		SDL_SetRenderTarget(renderer, backBuffer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SceneManager::getInstance()->render();

		SDL_SetRenderTarget(renderer, nullptr);
		SDL_RenderCopy(renderer, backBuffer, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
}