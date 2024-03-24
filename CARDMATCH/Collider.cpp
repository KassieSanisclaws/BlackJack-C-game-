#include "Collider.h"
#include "GameObjectVisitor.h"

Collider::Collider(Vector2D v, float w, float h) : position(v), w(w), h(h)
{ 
	top = false;
	right = false;
	bottom = false;
	left = false;
}

Collider::Collider(float x, float y, float w, float h) : position(x, y), w(w), h(h)
{ 
	top = false;
	right = false;
	bottom = false;
	left = false;
}

Collider::Collider(const Collider& other) : position(other.position), w(other.w), h(other.h)
{
	top = other.top;
	right = other.right;
	bottom = other.bottom;
	left = other.left;
}

Collider* Collider::clone()
{
	return new Collider(*this);
}

void Collider::accept(GameObjectVisitor& visitor)
{

}

void Collider::update()
{

}

void Collider::render()
{

}


Vector2D Collider::getCollider()
{
	Vector2D rect = { position.x, position.y };
	return rect;
}

bool Collider::checkCollision(Collider* a, Collider* b)
{
	float leftA = a->position.x;
	float leftB = b->position.x;
	float rightA = a->position.x + a->w;
	float rightB = b->position.x + b->w;
	float topA = a->position.y;
	float topB = b->position.y;
	float bottomA = a->position.y + a->h;
	float bottomB = b->position.y + b->h;

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
		return false;

	return true;
}

bool Collider::checkCollision(Collider* b)
{
	float leftA = position.x;
	float leftB = b->position.x;
	float rightA = position.x + w;
	float rightB = b->position.x + b->w;
	float topA = position.y;
	float topB = b->position.y;
	float bottomA = position.y + h;
	float bottomB = b->position.y + b->h;

	bottom = false; 
	top = false;
	left = false;
	right = false;

	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
		return false;

	float overlapLeft = rightA - leftB;
	float overlapRight = rightB - leftA;
	float overlapTop = bottomA - topB;
	float overlapBottom = bottomB - topA;

	float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

	if (minOverlap == overlapLeft) 
		left = true;
	else if (minOverlap == overlapRight) 
		right = true;
	else if (minOverlap == overlapTop) 
		top = true;
	else if (minOverlap == overlapBottom) 
		bottom = true;

	return true;
}