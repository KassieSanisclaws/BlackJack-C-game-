#include "Window.h"
#include "Renderer.h"
#include "Engine.h"
#include "SceneManager.h"
#include "GameLoop.h"

// Initialize SDL and create window and renderer
Window::Window(std::string t, int x, int y, int w, int h, std::string rendererType, bool full) : title(t), x(x), y(y), w(w), h(h), fullScreen(full)
{ 
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Uint32 flags = 0;

		std::cout << "SDL initializing..." << std::endl;

		if (full)
			flags = flags | SDL_WINDOW_FULLSCREEN;

		if(rendererType == "opengl")
			flags = flags | SDL_WINDOW_OPENGL;		

		window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);

		if (window != 0)
		{
			std::cout << "Window created..." << std::endl;

			Renderer::getInstance()->init(rendererType, window);

			renderer = Renderer::getInstance()->getRenderer();

			if (IMG_Init(IMG_INIT_PNG) < 0)
			{
				std::cout << "Error: initializing SDL_image: " << IMG_GetError() << std::endl;
			}

			if (TTF_Init() < 0)
			{
				std::cout << "Error: initializing SDL_ttf: " << TTF_GetError() << std::endl;
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0)
			{
				std::cout << "Error: initializing audio: " << SDL_GetError() << std::endl;
			}
		}
		else
			std::cout << "Error: window was not created" << std::endl;
	}
	else
		std::cout << "Error: SDL was not initialized" << std::endl;
}

// Shurtdown SDL and unload window and renderer
Window::~Window()
{
	std::cout << "Shutting down SDL..." << std::endl;

	Renderer::removeInstance();

	if (window != nullptr)
	{
		std::cout << "Removing window..." << std::endl;
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	else
		std::cout << "Error: Window could not be removed" << std::endl;
}

Window* Window::getInstance()
{
	if (instance)
		return instance;

	return nullptr;
}

// Singleton initialization
Window* Window::getInstance(std::string t, int x, int y, int w, int h, std::string deviceName, bool full)
{
	if (instance == nullptr)
		instance = new Window(t, x, y, w, h, deviceName, full);

	return instance;
}

// Singleton deletion
void Window::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

SDL_Window* Window::getWindow()
{
	return window;
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

// Main game loop update using user supplied function pointer
void Window::update()
{
	SceneManager::getInstance()->update();
}

// Main game loop render using user supplied function pointer and render to screen
void Window::render()
{
	Renderer::getInstance()->render();
}

// Singleton initialization
Window* Window::instance = nullptr;

SDL_Window* Window::window = nullptr;
SDL_Renderer* Window::renderer = nullptr;