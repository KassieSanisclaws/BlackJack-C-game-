#include "SFXComponent.h"
#include "ResourceManager.h"

SFXComponent::SFXComponent()
	: filename(""), playing(false), sfx(nullptr)
{ }

void SFXComponent::loadAsset(std::string goID, std::string filename)
{
	sfx = ResourceManager::getInstance()->loadSFX(goID, filename);
}

SFXComponent::~SFXComponent()
{
	ResourceManager::getInstance()->removeSFX(filename);
}

void SFXComponent::playSFX()
{
	Mix_VolumeChunk(sfx, MIX_MAX_VOLUME / 2);
	Mix_PlayChannel(-1, sfx, 1);
}