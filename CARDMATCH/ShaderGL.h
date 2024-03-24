#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include "SDL.h"
#include "SDL_opengl.h"

#include <gl/GL.h>
#include <gl/GLU.h>

#include "OpenGLImage.h"

class ImageGL;

typedef enum shaderType
{
	VERTEX = 0,
	FRAGMENT,
	PROGRAM
} ShaderType;

class ShaderGL
{
public:
	ShaderGL();
	ShaderGL(std::string, std::string);
	virtual ~ShaderGL();

	void applyShader();
	void removeShader();

	void setBool(const std::string&, bool) const;
	void setInt(const std::string&, int) const;
	void setFloat(const std::string&, float) const;

	void createShader(GLuint, GLuint);
	GLuint compileShader(const std::string&, ShaderType);
	std::string readShaderFile(const std::string&);

	void bindImage(const ImageGL&);
	void bindImage(const OpenGLImage&);
	void unbindImage();

	void setVertexAttribPointer(GLint, GLenum, GLboolean, GLsizei);

	GLuint gProgramID;
	GLint gVertexPos2DLocation;
	GLuint gVBO;
	GLuint gIBO;

	unsigned int shaderID;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	std::string vertexFilename;
	std::string fragmentFilename;
	std::string vertexCode;
	std::string fragmentCode;

protected:
	void checkCompileErrors(unsigned int, ShaderType);

	GLuint currentAttribIndex = 0;
	GLsizei currentOffset = 0;
};