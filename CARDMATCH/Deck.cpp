#include "Deck.h"

Deck::Deck()
{
	cards.reserve(NUMCARDS);

	gameObjectID = "deck";

	createCards();
	shuffle();
	layout();
}

Deck::~Deck()
{
	for (int i = 0; i < cards.size(); ++i)
		delete cards[i];
}

void Deck::update()
{
	std::vector<Card*>::iterator it = cards.begin();

	while (it != cards.end())
	{
		(*it)->update();

		++it;
	}
}

void Deck::render()
{
	std::vector<Card*>::iterator it = cards.begin();

	while (it != cards.end())
	{
		(*it)->render();

		++it;
	}
}

Deck* Deck::clone()
{
	return nullptr;
}

Card* Deck::getCardAt(int index)
{
	return cards[index];
}

void Deck::createCards()
{
	for (int i = 0; i < NUMCARDS / 2; ++i)
	{
		int rndCard = CHEST + rand() % (STAR - CHEST + 1);

		std::stringstream gameObjectName;
		gameObjectName << "card" << i;

		std::stringstream gameObjectNameDup;
		gameObjectNameDup << "card" << (i + (NUMCARDS / 2));

		Card* temp = new Card(gameObjectName.str(), "images/cards.png", 0, 0, 0, 0, 1, 12, rndCard);
		cards.push_back(temp);

		temp = temp->clone();
		temp->setGameObjectID(gameObjectNameDup.str());	
		cards.push_back(temp);
	}
}

void Deck::layout()
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			float x = 110 + (50 * j);
			float y = 100 + (75 * i);
			Vector2D v = { x, y };

			cards[j + (COLS * i)]->setPosition(v);
		}
	}
}

void Deck::shuffle()
{
	for (int i = 0; i < cards.size(); ++i)
	{
		int rndCard = rand() % FACES::STAR;
		Card* temp = cards[rndCard];
		cards[rndCard] = cards[i];
		cards[i] = temp;
	}
}

const int Deck::NUMCARDS = 18;
const int Deck::ROWS = 3;
const int Deck::COLS = 6;