#pragma once

#include <string>

#include "SDL.h"
#include "SDL_mixer.h"

#include "Object.h"

class ResourceManager;

class MusicComponent : public Object
{
public:
	MusicComponent();
	~MusicComponent();

	void loadAsset(std::string, std::string);

	void playMusic();

	bool playing;

	std::string filename;

private:
	Mix_Music* music;
};
