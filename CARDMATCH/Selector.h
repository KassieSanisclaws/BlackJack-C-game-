#pragma once

#include <string>

#include "Game.h"
#include "Sprite.h"

class Selector : public GameObject
{
public:
	Selector(std::string, std::string, int, int, int, int, int, int);
	Selector(const Selector&);
	~Selector();

	Selector* clone();

	void update();
	void render();

	Sprite* graphic;

private:
};