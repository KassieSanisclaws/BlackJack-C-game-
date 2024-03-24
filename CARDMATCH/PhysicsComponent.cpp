#include "PhysicsComponent.h"
#include "Collider.h"

PhysicsComponent::PhysicsComponent() : velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), startTime(0), endTime(0)
{ 
	collider = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{ 
	if(collider)
		delete collider;
}