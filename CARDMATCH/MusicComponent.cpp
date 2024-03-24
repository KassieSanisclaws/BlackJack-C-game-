#include "MusicComponent.h"
#include "ResourceManager.h"

MusicComponent::MusicComponent()
	: filename(""), playing(false), music(nullptr)
{ }

void MusicComponent::loadAsset(std::string goID, std::string filename)
{
	if (filename != "")
		music = ResourceManager::getInstance()->loadMusic(goID, filename);
}

MusicComponent::~MusicComponent()
{
	if (filename != "")
		ResourceManager::getInstance()->removeMusic(filename);
}

void MusicComponent::playMusic()
{
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(music, -1);
}