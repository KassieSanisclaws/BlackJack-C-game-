#pragma once

#include <vector>
#include <string>

#include "SDL.h"

#include "Object.h"

class ResourceManager;
class AnimationManager;
class TimeManager;

class AnimationComponent : public Object
{
public:
    AnimationComponent();

	void initialize(std::string gameObjectID);

	std::vector<int> currentSequence;
	std::string currentAnimation;
	int currentFrame;
	int startFrame;
	int endFrame;

	int fps;
	Uint32 startTime;
	Uint32 prevTime;

	bool animating;
	bool repeat;
	bool reverse;

private:
	ResourceManager* resourceManager;
	AnimationManager* animationManager;
	TimeManager* timeManager;
};