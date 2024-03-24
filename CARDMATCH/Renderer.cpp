#include "Renderer.h"
#include "Window.h"
#include "RendererFactory.h"
#include "DirectXRenderer.h"
#include "OpenGLRenderer.h"

Renderer::Renderer()
{
	renderer = nullptr;
}

Renderer::~Renderer()
{
	if(renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	delete rendererPIMPL;
}

Renderer* Renderer::getInstance()
{
	if (!instance)
		instance = new Renderer();

	return instance;
}

void Renderer::removeInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void Renderer::init(std::string driver, SDL_Window* window)
{
	rendererPIMPL = RendererFactory::getInstance(driver, window);

	rendererPIMPL->init();
}

void Renderer::render()
{
	rendererPIMPL->render();
}


SDL_Renderer* Renderer::getRenderer()
{
	return rendererPIMPL->getRenderer();
}

RendererFactory* Renderer::rendererPIMPL = nullptr;
Renderer* Renderer::instance = nullptr;
SDL_Renderer* Renderer::renderer = nullptr;