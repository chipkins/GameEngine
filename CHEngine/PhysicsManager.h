#pragma once

#include "Object.h"

typedef bool (*CollisionCallback)(Object* a, Object* b);
extern CollisionCallback Dispatch[Shape::count][Shape::count];

//PhysicsManager();
//~PhysicsManager();

/*typedef bool (PhysicsManager::*CollisionCallback)(Object* a, Object* b);
extern CollisionCallback Dispatch[Shape::count][Shape::count];*/

bool AABBvsAABB(Object* a, Object* b);
bool CirclevsCircle(Object* a, Object* b);
bool AABBvsCircle(Object* a, Object* b);
bool CirclevsAABB(Object* a, Object* b);
bool NoCollision(Object* a, Object* b);