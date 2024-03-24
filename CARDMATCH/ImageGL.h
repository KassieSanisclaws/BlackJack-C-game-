#pragma once

#include <string>

#include <GL/glew.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include <string>

#include "GameObject.h"
#include "Vector2D.h"
#include "BaseShaderGL.h"
#include "SDLOpenGLCoordinate.h"

class BaseShaderGL;
class QuadGL;

class ImageGL : public GameObject
{
public:
	ImageGL(std::string, std::string, float, float);
	ImageGL(const ImageGL&);
	~ImageGL();

	ImageGL* clone();

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
	BaseShaderGL shader;

	std::string filename;
};