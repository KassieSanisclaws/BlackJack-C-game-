#pragma once

#include <string>

#include <GL/glew.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include "GameObject.h"
#include "Vector2D.h"

class QuadGL;

class OpenGLImage : public GameObject
{
public:
	OpenGLImage(std::string, std::string, float, float);
	OpenGLImage(const OpenGLImage&);
	~OpenGLImage();

	OpenGLImage* clone();

	void update();
	void render();

	Vector2D position;
	float width;
	float height;

	GLuint textureID;
	float* vertices;
	QuadGL* quad;

	unsigned int indices[6] = { 0, 1, 3, 1, 2, 3 };

private:
	SDL_Surface* surface;

	std::string filename;
};