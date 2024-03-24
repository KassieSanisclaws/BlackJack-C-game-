#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

#include "QuadGL.h"

#include "GameSettings.h"

class SDLOpenGLCoordinate 
{
public:
    static void drawSDL(int, int, int, int, int=GameSettings::SCREEN_WIDTH, int=GameSettings::SCREEN_HEIGHT);
    static float* createVertices(int, int, int, int, int=GameSettings::SCREEN_WIDTH, int=GameSettings::SCREEN_HEIGHT);
    static QuadGL* generateQuad(int, int, int, int, int=GameSettings::SCREEN_WIDTH, int=GameSettings::SCREEN_HEIGHT);
};