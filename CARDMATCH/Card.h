#pragma once

#include <string>
#include <vector>

#include "Vector2D.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"

typedef enum faces
{
	BLANK = 0,
	CHEST = 6,
	COIN = 7,
	FLOWER = 8,
	MUSHROOM = 9,
	STAR = 10,
	SELECTOR = 11
} FACES;

class Card : public GameObject
{
public:
	Card(std::string, std::string, int, int, int, int, int, int, int);
	Card(const Card&);
	~Card();

	void initialize();

	void update();
	void render();

	Card* clone();

	void play(std::string, int, bool = false, bool = false);

	void setPosition(Vector2D);
	Vector2D getPosition();

	void setCurrentFrame(int);

	void setFace(int);
	int getFace();

	bool isTurned();
	void setTurned(bool);

	std::string getFaceName();

	Sprite* graphic;

private:
	int face;
	bool turned;

	static const std::vector<int> chestAnimation;
	static const std::vector<int> coinAnimation;
	static const std::vector<int> flowerAnimation;
	static const std::vector<int> mushroomAnimation;
	static const std::vector<int> starAnimation;
};