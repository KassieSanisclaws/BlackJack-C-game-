#include "AnimationManager.h"

AnimationManager* AnimationManager::getInstance()
{
	if (instance == nullptr)
		instance = new AnimationManager();

	return instance;
}

void AnimationManager::removeInstance()
{
	if (instance != nullptr)
		delete instance;
}

std::vector<SDL_Rect> AnimationManager::getFrameMap(std::string goID, std::string animationName)
{
	std::unordered_map<std::string, std::string>::iterator it = gameObjects.find(goID);
	std::vector<SDL_Rect> sequence;

	if (it != gameObjects.end())
	{
		std::unordered_multimap<std::string, std::vector<SDL_Rect>>::iterator iter = frameMap.find((*it).second);
		std::vector<int> animationSequence = animationMap[goID + animationName];

		if (iter != frameMap.end())
			 sequence = (*iter).second;
	}

	return sequence;
}

SDL_Rect AnimationManager::getCurrentFrame(std::string goID, std::string animationName, int frame)
{
	int currentFrame;
	SDL_Rect currentRect { 0, 0, 0, 0 };

	std::unordered_map<std::string, std::string>::iterator it = gameObjects.find(goID);

	if (it != gameObjects.end())
	{
		std::string frameMapName = goID + animationName;
		std::vector<int> animationSequence = animationMap[frameMapName];

		if (frame >= 0 && frame < animationSequence.size())
		{
			currentFrame = animationSequence[frame];

			std::unordered_multimap<std::string, std::vector<SDL_Rect>>::iterator it = frameMap.find(frameMapName);

			if (it != frameMap.end())
			{
				std::vector<SDL_Rect> sequence = (*it).second;

				currentRect = sequence[currentFrame];
			}
		}
	}
	
	return currentRect;
}

int AnimationManager::getAnimationLength(std::string goID, std::string animationName)
{
	std::unordered_map<std::string, std::string>::iterator it = gameObjects.find(animationName);
	std::vector<int> animationSequence;

	if (it != gameObjects.end())
	{
		animationSequence = animationMap[animationName];

		return animationSequence.size();
	}

	std::cout << "Animation " << animationName << " does not exist..." << std::endl;

	return 0;
}

AnimationManager* AnimationManager::instance = nullptr;