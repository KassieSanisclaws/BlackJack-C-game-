#pragma once

#include <string>

#include "SDL.h"

class Window;
class RendererFactory;

class Renderer
{
    friend class Window;

public:
    ~Renderer();

    static void init(std::string, SDL_Window*);

    void render();

    static Renderer* getInstance();
    static void removeInstance();

    static SDL_Renderer* getRenderer();

private:
    Renderer();

    static RendererFactory* rendererPIMPL;
    
    static SDL_Renderer* renderer;
    static Renderer* instance;
};