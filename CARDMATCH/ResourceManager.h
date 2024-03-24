#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

class Renderer;
class GameObject;
class AnimationManager;

class ResourceManager
{
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	static void removeInstance();

	SDL_Texture* loadTexture(std::string goID, std::string filename, int = 1, int = 1, int = 0, int = 0);
	TTF_Font* loadFont(std::string goID, std::string filename, int ptsize);
	Mix_Music* loadMusic(std::string goID, std::string filename);
	Mix_Chunk* loadSFX(std::string goID, std::string filename);

	SDL_Texture* findTexture(std::string filename);
	TTF_Font* findFont(std::string filename);
	Mix_Music* findMusic(std::string filename);
	Mix_Chunk* findSFX(std::string filename);

	void addGameObject(GameObject*, int);

	void removeFont(std::string);
	void removeMusic(std::string);
	void removeSFX(std::string);

	static std::unordered_map<std::string, SDL_Texture*> textureMap;
	static std::unordered_map<std::string, TTF_Font*> fontMap;
	static std::unordered_map<std::string, Mix_Music*> musicMap;
	static std::unordered_map<std::string, Mix_Chunk*> sfxMap;
	static std::map<int, GameObject*> gameObjects;

private:
	ResourceManager();

	Renderer* renderer;
	AnimationManager* animationManager;

	std::unordered_map<std::string, std::string> resourceMap;

	static ResourceManager* instance;
};