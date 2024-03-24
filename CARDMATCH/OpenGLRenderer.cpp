#include "OpenGLRenderer.h"
#include "SceneManager.h"

OpenGLRenderer::OpenGLRenderer(SDL_Window* w)
{
	window = w;

	renderer = nullptr;
}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_GL_DeleteContext(glContext);
}

void OpenGLRenderer::init()
{
	glContext = SDL_GL_CreateContext(window);
	
	if (glContext)
	{
		std::cout << "OpenGL context created..." << std::endl;
		int width, height;

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		}

		SDL_GetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0);
	}
	else
	{
		std::cout << "Error: OpenGL context could not be created - " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, 3, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer != 0)
	{
		std::cout << "Renderer created..." << std::endl;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	else
		std::cout << "Error: Renderer was not created" << std::endl;
}

void OpenGLRenderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::getInstance()->render();

	SDL_GL_SwapWindow(window);
}

SDL_GLContext OpenGLRenderer::getGLContext()
{
	return glContext;
}

SDL_GLContext OpenGLRenderer::glContext;