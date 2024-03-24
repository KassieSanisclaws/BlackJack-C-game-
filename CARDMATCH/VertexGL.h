#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

class VertexGL
{
public:
	VertexGL(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 0.0f, GLfloat tx = 0.0f, GLfloat ty = 0.0f) :
		x(x), y(y), z(z), r(r), g(g), b(b), a(a), tx(tx), ty(ty)
	{ }

	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

	GLfloat tx;
	GLfloat ty;
};