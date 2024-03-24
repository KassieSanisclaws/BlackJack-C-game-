#pragma once

#include "SDL.h"

#include "GameObject.h"
#include "Vector2D.h"

class Collider : public GameObject
{
public:
	Collider(Vector2D, float, float);
	Collider(float, float, float, float);
	Collider(const Collider&);
	~Collider() = default;

	Collider* clone();
	void accept(GameObjectVisitor&);

	void update();
	void render();

	Vector2D getCollider();

	bool checkCollision(Collider*);
	static bool checkCollision(Collider*, Collider*);

	Vector2D position;
	float w;
	float h;

	bool top;
	bool right;
	bool bottom;
	bool left;
};