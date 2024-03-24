#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "SDL.h"

class AnimationManager
{
public:
	static AnimationManager* getInstance();
	static void removeInstance();

	SDL_Rect getCurrentFrame(std::string, std::string, int);
	int getAnimationLength(std::string, std::string);
	std::vector<SDL_Rect> getFrameMap(std::string, std::string);

	std::unordered_multimap<std::string, std::vector<SDL_Rect>> frameMap;
	std::unordered_map<std::string, std::vector<int>> animationMap;
	std::unordered_multimap<std::string, std::string> gameObjects;

private:
	static AnimationManager* instance;
};