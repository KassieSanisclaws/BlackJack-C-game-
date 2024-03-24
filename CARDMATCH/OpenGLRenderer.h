#pragma once

#include <iostream>

#include <GL/glew.h>

#include "SDL.h"
#include "SDL_opengl.h"

#include <GL/GL.h>
#include <GL/GLU.h>

#include "RendererFactory.h"

class OpenGLRenderer : public RendererFactory
{
public:
	OpenGLRenderer(SDL_Window*);
	~OpenGLRenderer();

	void init();

	void render();

	static SDL_GLContext getGLContext();

private:
	static SDL_GLContext glContext;
};