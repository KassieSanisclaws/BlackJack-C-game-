#include "Sprite.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "AnimationManager.h"
#include "TimeManager.h"
#include "GameObjectVisitor.h"
#include "Collider.h"
#include "Game.h"

Sprite::Sprite() : GameObject()
{
	resourceManager = ResourceManager::getInstance();
	animationManager = AnimationManager::getInstance();
	timeManager = TimeManager::getInstance();
}

Sprite::Sprite(std::string goID, std::string filename, float x, float y, int w, int h, int rows, int cols)
{
	GraphicsComponent* gc = new GraphicsComponent();
	AnimationComponent* ac = new AnimationComponent();
	PhysicsComponent* pc = new PhysicsComponent();

	properties = new GameObjectProperties(gc, ac, pc);

	gameObjectID = goID;
	gc->filename = filename;
	gc->position = { x, y };
	gc->w = w;
	gc->h = h;
	gc->rows = rows;
	gc->cols = cols;

	loadAsset(goID);

	ac->initialize(goID);

	pc->collider = new Collider({ x, y }, w, h);

	resourceManager = ResourceManager::getInstance();
	animationManager = AnimationManager::getInstance();
	timeManager = TimeManager::getInstance();
}

Sprite::Sprite(GameObjectProperties* properties) 
    : GameObject(properties)
{
	GraphicsComponent* gc = new GraphicsComponent();
	PhysicsComponent* pc = new PhysicsComponent();

	resourceManager = ResourceManager::getInstance();
	animationManager = AnimationManager::getInstance();
	timeManager = TimeManager::getInstance();
}

Sprite::Sprite(const Sprite& other)
{
	GraphicsComponent* gc = new GraphicsComponent();
	AnimationComponent* ac = new AnimationComponent();
	PhysicsComponent* pc = new PhysicsComponent();

	properties = new GameObjectProperties(gc, ac, pc);

	resourceManager = ResourceManager::getInstance();
	animationManager = AnimationManager::getInstance();
	timeManager = TimeManager::getInstance();
}

Sprite::~Sprite()
{ }

Sprite* Sprite::clone()
{
    return new Sprite(*this);
}

void Sprite::accept(GameObjectVisitor& visitor)
{

}

void Sprite::update()
{
	GraphicsComponent* gc = properties->graphicsComponent;
	AnimationComponent* ac = properties->animationComponent;
	PhysicsComponent* pc = properties->physicsComponent;

	if (ac->animating)
	{
		long currentTime = TimeManager::getInstance()->get(gameObjectID);
		float deltaTime = static_cast<float>(currentTime) - ac->startTime;

		if (ac->startTime == 0.0f) 
		{
			ac->startTime = currentTime;
			ac->currentFrame = ac->startFrame;
			deltaTime = 0.0f;
		}

		if (deltaTime >= 1000.0f / ac->fps)
			ac->currentFrame = (static_cast<int>(((deltaTime * static_cast<float>(ac->fps)) / 1000) - ac->startFrame) % ((ac->endFrame + 1) - ac->startFrame)) + ac->startFrame;

		if (!ac->repeat && ac->currentFrame == ac->endFrame)
			ac->animating = false;
	}
	
	pc->collider->position = gc->position;
}

void Sprite::render()
{
	GraphicsComponent* gc = properties->graphicsComponent;
	AnimationComponent* ac = properties->animationComponent;

	if (gc->visible)
	{
		std::vector<SDL_Rect> frameMap = animationManager->getFrameMap(gameObjectID, ac->currentAnimation);

		SDL_Rect source = frameMap[ac->currentSequence[ac->currentFrame]];
		SDL_Rect destination = getRect();

		SDL_RenderCopyEx(Renderer::getInstance()->getRenderer(), gc->texture, &source, &destination, gc->angle, nullptr, gc->orientation);
	}
}

void Sprite::loadAsset(std::string goID)
{
	properties->graphicsComponent->loadAsset(goID);
}

void Sprite::addAnimation(std::string animationID, const std::vector<int> sequence)
{
	std::cout << "Adding animation " << gameObjectID + animationID << "..." << std::endl;
	animationManager->animationMap[gameObjectID + animationID] = sequence;
}

void Sprite::play(int startFrame, int endFrame, int fps, bool r, bool rev, bool flip)
{
	GraphicsComponent* gc = properties->graphicsComponent;
	AnimationComponent* ac = properties->animationComponent;

	ac->currentSequence = animationManager->animationMap[gameObjectID + ac->currentAnimation];

	if (rev)
		std::reverse(ac->currentSequence.begin(), ac->currentSequence.end());

	if (startFrame < 0 || endFrame >= ac->currentSequence.size())
	{
		std::cout << "Animation out of range" << std::endl;
		return;
	}
	else
	{
		std::cout << "Starting animation " << gameObjectID + ac->currentAnimation << "..." << std::endl;

		ac->animating = true;

		ac->fps = fps;
		ac->repeat = r;
		ac->reverse = rev;

		ac->startFrame = startFrame;
		ac->endFrame = endFrame;

		if (flip)
			gc->orientation = SDL_FLIP_HORIZONTAL;
		else
			gc->orientation = SDL_FLIP_NONE;
	}
}

void Sprite::play(std::string animationID, int fps, bool r, bool rev, bool flip)
{
	GraphicsComponent* gc = properties->graphicsComponent;
	AnimationComponent* ac = properties->animationComponent;

	ac->currentSequence = animationManager->animationMap[gameObjectID + animationID];

	if (rev)
		std::reverse(ac->currentSequence.begin(), ac->currentSequence.end());

	if (!ac->currentSequence.empty())
	{
		std::cout << "Starting animation " << gameObjectID + animationID << "..." << std::endl;

		ac->fps = fps;

		ac->currentAnimation = animationID;
		ac->startFrame = 0;
		ac->endFrame = ac->currentSequence.size() - 1;

		ac->animating = true;
		ac->repeat = r;
		ac->reverse = rev;

		if (flip)
			gc->orientation = SDL_FLIP_HORIZONTAL;
		else
			gc->orientation = SDL_FLIP_NONE;
	}
	else
		std::cout << "Animation " << animationID << "does not exist" << std::endl;
}

void Sprite::stop()
{
	AnimationComponent* ac = properties->animationComponent;

	ac->animating = false;
}

void Sprite::setCurrentFrame(int frame)
{
	AnimationComponent* ac = properties->animationComponent;

	std::vector<int> sequence = animationManager->animationMap[gameObjectID + ac->currentAnimation];

	if (frame < 0 || frame >= sequence.size())
		ac->currentFrame = 0;
	else
		ac->currentFrame = frame;
}

Collider* Sprite::getCollider()
{
	return properties->physicsComponent->collider;
}

bool Sprite::checkCollision(Collider* b)
{
	return properties->physicsComponent->collider->checkCollision(b);
}

int Sprite::getCurrentFrame()
{
	AnimationComponent* ac = properties->animationComponent;

	return ac->currentFrame;
}

SDL_Texture* Sprite::getFrame()
{
	GraphicsComponent* gc = properties->graphicsComponent;

	return gc->texture;
}

bool Sprite::isAnimating()
{
	AnimationComponent* ac = properties->animationComponent;

	return ac->animating;
}

std::string Sprite::getCurrentAnimation()
{
	AnimationComponent* ac = properties->animationComponent;

	return ac->currentAnimation;
}

long Sprite::getStartTime()
{
	AnimationComponent* ac = properties->animationComponent;
	return ac->startTime;
}

long Sprite::getCurrentTime()
{
	return timeManager->get(gameObjectID);
}

long Sprite::getEndTime()
{
	PhysicsComponent* pc = properties->physicsComponent;

	return pc->endTime;
}

void Sprite::setEndTime(long time)
{
	PhysicsComponent* pc = properties->physicsComponent;

	pc->endTime = time;
}

float Sprite::getDelta()
{
	AnimationComponent* ac = properties->animationComponent;
	PhysicsComponent* pc = properties->physicsComponent;

	Uint32 currentTime = timeManager->get(gameObjectID);
	float deltaTime = currentTime - pc->endTime;

	return deltaTime;
}

std::string Sprite::getFilename()
{
    return properties->graphicsComponent->filename;
}

Vector2D Sprite::getPosition()
{
	return properties->graphicsComponent->position;
}

int Sprite::getWidth()
{
	return properties->graphicsComponent->w / properties->graphicsComponent->cols;
}

int Sprite::getHeight()
{
	return properties->graphicsComponent->h / properties->graphicsComponent->rows;
}

void Sprite::setPosition(Vector2D v)
{
	properties->graphicsComponent->position = v;
}

double Sprite::getAngle()
{
	return properties->graphicsComponent->angle;
}

void Sprite::setAngle(double angle)
{
	properties->graphicsComponent->angle = angle;
}

SDL_Rect Sprite::getRect()
{
	GraphicsComponent* gc = properties->graphicsComponent;

	return SDL_Rect{ static_cast<int>(gc->position.x), static_cast<int>(gc->position.y), gc->w / gc->cols, gc->h / gc->rows };
}

bool Sprite::isVisible()
{
	return properties->graphicsComponent->visible;
}

void Sprite::setVisible(bool visible)
{
	properties->graphicsComponent->visible = visible;
}