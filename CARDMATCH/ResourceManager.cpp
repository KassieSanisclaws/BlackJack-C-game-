#include "ResourceManager.h"
#include "Renderer.h"
#include "AnimationManager.h"

ResourceManager::ResourceManager()
{
	renderer = Renderer::getInstance();

	animationManager = AnimationManager::getInstance();
}

ResourceManager::~ResourceManager()
{ 
	AnimationManager::removeInstance();

	auto it = gameObjects.begin();
	static std::unordered_map<std::string, Mix_Music*> musicMap;
	static std::unordered_map<std::string, Mix_Chunk*> sfxMap;
	static std::map<int, GameObject*> gameObjects;

	SDL_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
}

ResourceManager* ResourceManager::getInstance()
{
	if (instance == nullptr)
		instance = new ResourceManager();

	return instance;
}

void ResourceManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

TTF_Font* ResourceManager::loadFont(std::string goID, std::string filename, int ptsize)
{
	TTF_Font* font = TTF_OpenFont(filename.c_str(), ptsize);

	if (!font)
	{
		std::cout << "Font could not open - " << SDL_GetError() << std::endl;

		return nullptr;
	}

	std::unordered_map<std::string, TTF_Font*>::iterator it = fontMap.find(filename);

	if (it != fontMap.end())
	{
		std::cout << "Font " << filename << " already loaded..." << std::endl;
		font = (*it).second;
	}
	else
	{
		std::cout << "Loading font " << filename << "..." << std::endl;
		resourceMap[goID] = filename;
		fontMap[filename] = font;
	}

	return font;	
}

SDL_Texture* ResourceManager::loadTexture(std::string goID, std::string filename, int totalRows, int totalCols, int offsetX, int offsetY)
{
	SDL_Texture* texture;
	std::unordered_map<std::string, SDL_Texture*>::iterator it = textureMap.find(filename);

	if (it != textureMap.end())
	{
		std::cout << "Sprite " << filename << " already loaded..." << std::endl;
		texture = (*it).second;
	}
	else
	{
		texture = IMG_LoadTexture(renderer->getRenderer(), filename.c_str());

		std::cout << "Loading sprite " << filename << "..." << std::endl;

		if (texture == nullptr)
		{
			std::cout << "Error: Unable to open sprite - " << IMG_GetError() << std::endl;
			return nullptr;
		}
	}

	int w;
	int h;

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	w /= totalCols;
	h /= totalRows;

	std::vector<SDL_Rect> frameInfo;
	std::vector<int> animationSequence;
	std::string animationName = "default";

	frameInfo.reserve(totalRows * totalCols);

	for (int i = 0; i < totalRows; ++i)
	{
		for (int j = 0; j < totalCols; ++j)
		{
			SDL_Rect temp;

			temp.x = (j * w) + offsetX;
			temp.y = (i * h) + offsetY;
			temp.w = w;
			temp.h = h;

			frameInfo.push_back(temp);
			animationSequence.push_back(i * totalCols + j);
		}
	}

	if (totalRows == 1 && totalCols > 1 || totalRows > 1 && totalCols == 1 || totalRows > 1 && totalCols > 1)
	{
		animationManager->frameMap.insert({ goID + animationName, frameInfo });
		animationManager->animationMap[goID + animationName] = animationSequence;
		animationManager->gameObjects.insert({ goID, goID + animationName });
	}

	resourceMap[goID] = filename;
	textureMap[filename] = texture;

	return texture;
}

Mix_Music* ResourceManager::loadMusic(std::string goID, std::string filename)
{
	Mix_Music* music = Mix_LoadMUS(filename.c_str());

	if (!music)
	{
		std::cout << "Music could not be open - " << SDL_GetError() << std::endl;

		return nullptr;
	}
	
	std::unordered_map<std::string, Mix_Music*>::iterator it = musicMap.find(filename);

	if (it != musicMap.end())
	{
		std::cout << "Music " << filename << " already loaded..." << std::endl;
		music = (*it).second;
	}
	else
	{
		std::cout << "Loading music " << filename << "..." << std::endl;
		resourceMap[goID] = filename;
		musicMap[filename] = music;
	}

	return music;
}

Mix_Chunk* ResourceManager::loadSFX(std::string goID, std::string filename)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());

	if (!chunk)
	{
		std::cout << "SFX could not be open - " << SDL_GetError() << std::endl;

		return nullptr;
	}

	std::unordered_map<std::string, Mix_Chunk*>::iterator it = sfxMap.find(filename);

	if (it != sfxMap.end())
	{
		std::cout << "SFX " << filename << " already loaded..." << std::endl;
		chunk = (*it).second;
	}
	else
	{
		std::cout << "Loading SFX " << filename << "..." << std::endl;
		resourceMap[goID] = filename;
		sfxMap[filename] = chunk;
	}

	return chunk;
}

SDL_Texture* ResourceManager::findTexture(std::string filename)
{
	SDL_Texture* texture = textureMap[filename];
	
	if (texture == nullptr)
	{
		std::cout << "Error: Unable to find resource " << filename << std::endl;
		return nullptr;
	}

	return texture;
}

TTF_Font* ResourceManager::findFont(std::string filename)
{
	TTF_Font* font = fontMap[filename];

	if (font == nullptr)
	{
		std::cout << "Error: Unable to find resource " << filename << std::endl;
		return nullptr;
	}

	return font;
}

Mix_Music* ResourceManager::findMusic(std::string filename)
{
	Mix_Music* music = musicMap[filename];

	if (music == nullptr)
	{
		std::cout << "Error: Unable to find resource " << filename << std::endl;
		return nullptr;
	}

	return music;
}

Mix_Chunk* ResourceManager::findSFX(std::string filename)
{
	Mix_Chunk* chunk = sfxMap[filename];

	if (chunk == nullptr)
	{
		std::cout << "Error: Unable to find resource " << filename << std::endl;
		return nullptr;
	}

	return chunk;
}

void ResourceManager::removeFont(std::string filename)
{
	TTF_Font* f = ResourceManager::getInstance()->findFont(filename);

	if (!f)
	{
		TTF_CloseFont(f);
	}
}

void ResourceManager::removeMusic(std::string filename)
{
	Mix_Music* music = ResourceManager::getInstance()->findMusic(filename);

	if (music)
		Mix_FreeMusic(music);
}

void ResourceManager::removeSFX(std::string filename)
{
	Mix_Chunk* chunk = ResourceManager::getInstance()->findSFX(filename);

	if (chunk)
		Mix_FreeChunk(chunk);
}

void ResourceManager::addGameObject(GameObject* o, int depth)
{
	gameObjects[depth] = o;
}

std::unordered_map<std::string, TTF_Font*> ResourceManager::fontMap;
std::unordered_map<std::string, Mix_Music*> ResourceManager::musicMap;
std::unordered_map<std::string, Mix_Chunk*> ResourceManager::sfxMap;
std::unordered_map<std::string, SDL_Texture*> ResourceManager::textureMap;
std::map<int, GameObject*> ResourceManager::gameObjects;
ResourceManager* ResourceManager::instance = nullptr;