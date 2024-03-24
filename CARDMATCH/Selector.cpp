#include "Selector.h"

Selector::Selector(std::string goID, std::string filename, int x, int y, int w, int h, int r, int c)
{
	gameObjectID = goID;

	graphic = new Sprite(goID, filename, x, y, w, r, r, c);

	graphic->setCurrentFrame(11);
}

Selector::Selector(const Selector& other)
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
}

Selector::~Selector()
{
	delete graphic;
}

Selector* Selector::clone()
{
	return new Selector(*this);
}

void Selector::update()
{
	graphic->update();
}

void Selector::render()
{
	graphic->render();
}