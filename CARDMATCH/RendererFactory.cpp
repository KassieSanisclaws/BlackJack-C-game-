#include "RendererFactory.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"

RendererFactory::~RendererFactory()
{
	if (renderer != nullptr)
	{
		std::cout << "Removing renderer..." << std::endl;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	else
		std::cout << "Error: Renderer could not be removed" << std::endl;
}

RendererFactory* RendererFactory::getInstance(std::string driver, SDL_Window* window)
{
	if (driver == "direct3d")
		return new DirectXRenderer(window);
	else if (driver == "opengl")
		return new OpenGLRenderer(window);

	return nullptr;
}

SDL_Renderer* RendererFactory::getRenderer()
{
	return renderer;
}