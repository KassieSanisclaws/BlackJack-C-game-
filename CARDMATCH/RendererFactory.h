#pragma once

#include <iostream>
#include <string>

#include "SDL.h"

class RendererFactory
{
public:
    virtual ~RendererFactory();

    static RendererFactory* getInstance(std::string, SDL_Window*);

    virtual void init() = 0;
    virtual void render() = 0;

    virtual SDL_Renderer* getRenderer();

protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
};