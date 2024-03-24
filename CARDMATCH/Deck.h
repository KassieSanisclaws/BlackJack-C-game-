#pragma once

#include <vector>
#include <iostream>
#include <sstream>

#include "Game.h"
#include "GameObject.h"
#include "Card.h"

class Deck : public GameObject
{
public:
	Deck();
	~Deck();

	void update();
	void render();

	Deck* clone();

	Card* getCardAt(int);

	void createCards();
	void layout();
	void shuffle();

	static const int NUMCARDS;
	static const int ROWS;
	static const int COLS;

	std::vector<Card*> cards;
};