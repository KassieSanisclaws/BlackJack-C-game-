#pragma once

#include <string>

#include "SDL.h"
#include "SDL_mixer.h"

#include "Object.h"

class ResourceManager;

class SFXComponent : public Object
{
public:
	SFXComponent();
	~SFXComponent();

	void loadAsset(std::string, std::string);

	void playSFX();

	bool playing;

	std::string filename;

private:
	Mix_Chunk* sfx;
};
