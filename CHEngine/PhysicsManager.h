#pragma once

#include "Object.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	bool CheckCollision(Object* a, Object* b);
	bool AABBvsAABB(Object* a, Object* b);
	bool CirclevsCircle(Object* a, Object* b);
	bool AABBvsCircle(Object* a, Object* b);
	bool CirclevsAABB(Object* a, Object* b);
};