#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

class Engine;
class GameLoop;

class Window
{
	// Game object can access private members of Window
	friend class Engine;
	friend class GameLoop;

public:
	// Singleton method to return instance
	static Window* getInstance();
	static Window* getInstance(std::string, int, int, int, int, std::string="directx", bool = false);

	// Singleton destructor
	static void removeInstance();

	static SDL_Window* getWindow();
	static SDL_Renderer* getRenderer();

private:
	Window(std::string, int, int, int, int, std::string, bool = false);
	~Window();

	// Main game loop update processing
	static void update();

	// Main game loop render processing to window
	static void render();

	int x;
	int y;
	int w;
	int h;

	std::string title;
	bool fullScreen;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	// Singleton
	static Window* instance;
};