#include "OpenGLImage.h"
#include "GameSettings.h"
#include "QuadGL.h"
#include "SDLOpenGLCoordinate.h"

OpenGLImage::OpenGLImage(std::string goID, std::string f, float x, float y) : GameObject(), position(x, y)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gameObjectID = goID;

	filename = f;

	GLenum format = 0;
	surface = IMG_Load(filename.c_str());

	if (!surface)
	{
		std::cout << "Error loading image..." << std::endl;
	}

	width = surface->w;
	height = surface->h;

	if (surface->format->BytesPerPixel == 3)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
	}
	else if (surface->format->BytesPerPixel == 4)
	{
		format = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
	}

	if (surface->pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	quad = SDLOpenGLCoordinate::generateQuad(0, 0, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT);

	vertices = SDLOpenGLCoordinate::createVertices(0, 0, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT);
}

OpenGLImage::OpenGLImage(const OpenGLImage& other) : position(other.position)
{
	gameObjectID = other.gameObjectID;

	surface = nullptr;
	textureID = other.textureID;

	width = other.width;
	height = other.height;
}

OpenGLImage::~OpenGLImage()
{
	delete vertices;
	delete quad;

	SDL_FreeSurface(surface);
}

OpenGLImage* OpenGLImage::clone()
{
	return new OpenGLImage(*this);
}

void OpenGLImage::update()
{

}

void OpenGLImage::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}