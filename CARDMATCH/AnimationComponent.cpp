#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "TimeManager.h"

AnimationComponent::AnimationComponent()
{
	resourceManager = ResourceManager::getInstance();
	animationManager = AnimationManager::getInstance();
	timeManager = TimeManager::getInstance();
	
	animating = false;
	reverse = false;
	repeat = false;
}

void AnimationComponent::initialize(std::string gameObjectID)
{
	currentAnimation = "default";

	// Get default animation to determine length
	currentSequence = animationManager->animationMap[gameObjectID + currentAnimation];

	fps = 0;
	currentFrame = 0;
	startFrame = currentSequence[0];
	endFrame = currentSequence.size() - 1;

	// Time Initialization
	timeManager->addTimer(gameObjectID, true);
	timeManager->start(gameObjectID);
	startTime = 0;
	prevTime = startTime;
}