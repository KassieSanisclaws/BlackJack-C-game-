#include "Card.h"
#include "TimeManager.h"

Card::Card(std::string cardID, std::string filename, int x, int y, int w, int h, int r, int c, int f) : GameObject()
{
	gameObjectID = cardID;

	graphic = new Sprite(cardID, filename, x, y, w, h, r, c);

	face = f;

	initialize();
}

Card::Card(const Card& other)
{
	std::string goID = other.gameObjectID;
	std::string filename = other.graphic->getFilename();
	float x = other.graphic->getPosition().x;
	float y = other.graphic->getPosition().y;
	int w = other.graphic->getWidth();
	int h = other.graphic->getHeight();
	int rows = other.graphic->properties->graphicsComponent->rows;
	int cols = other.graphic->properties->graphicsComponent->cols;

	graphic = new Sprite(goID, filename, x, y, w, h, rows, cols);

	face = other.face;

	initialize();
}

Card::~Card()
{
	delete graphic;
}

void Card::initialize()
{
	graphic->setCurrentFrame(FACES::BLANK);

	turned = false;

	std::string aniFace = getFaceName();

	if(aniFace == "chest")
		graphic->addAnimation("chest", chestAnimation);
	else if(aniFace == "coin")
		graphic->addAnimation("coin", coinAnimation);
	else if (aniFace == "flower")
		graphic->addAnimation("flower", flowerAnimation);
	else if (aniFace == "mushroom")
		graphic->addAnimation("mushroom", mushroomAnimation);
	else if (aniFace == "star")
		graphic->addAnimation("star", starAnimation);
}

void Card::update()
{
	graphic->update();
}

void Card::render()
{
	graphic->render();
}

Card* Card::clone()
{
	return new Card(*this);
}

void Card::play(std::string animation, int fps, bool repeat, bool reverse)
{
	graphic->play(animation, fps, repeat, reverse);
}

void Card::setCurrentFrame(int frame)
{
	graphic->setCurrentFrame(frame);
}

void Card::setPosition(Vector2D v)
{
	graphic->setPosition(v);
}

Vector2D Card::getPosition()
{
	return graphic->getPosition();
}

void Card::setFace(int f)
{
	face = f;
}

int Card::getFace()
{
	return face;
}

void Card::setTurned(bool t)
{
	turned = t;
}

bool Card::isTurned()
{
	return turned;
}

std::string Card::getFaceName()
{
	std::string faceName;

	switch (face)
	{
	case FACES::CHEST:
		faceName = "chest";
		break;
	case FACES::COIN:
		faceName = "coin";
		break;
	case FACES::FLOWER:
		faceName = "flower";
		break;
	case FACES::MUSHROOM:
		faceName = "mushroom";
		break;
	case FACES::STAR:
		faceName = "star";
		break;
	}

	return faceName;
}

const std::vector<int> Card::chestAnimation = { 0, 1, 2, 3, 4, 5, 6 };
const std::vector<int> Card::coinAnimation = { 0, 1, 2, 3, 4, 5, 7 };
const std::vector<int> Card::flowerAnimation = { 0, 1, 2, 3, 4, 5, 8 };
const std::vector<int> Card::mushroomAnimation = { 0, 1, 2, 3, 4, 5, 9 };
const std::vector<int> Card::starAnimation = { 0, 1, 2, 3, 4, 5, 10 };