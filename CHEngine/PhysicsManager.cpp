#include "PhysicsManager.h"
#include "Shape.h"

CollisionCallback Dispatch[Shape::count][Shape::count] =
{
	{
		&AABBvsAABB, &AABBvsCircle, &NoCollision
	},
	{
		&CirclevsAABB, &CirclevsCircle, &NoCollision
	},
	{
		&NoCollision, &NoCollision, &NoCollision
	}
};

//PhysicsManager::PhysicsManager()
//{
//}
//
//PhysicsManager::~PhysicsManager()
//{
//}

//bool PhysicsManager::CheckCollision(Object * a, Object * b)
//{
//	if (a->body.shape->GetType() == Shape::noCollide)
//	{
//		return false;
//	}
//	else if (a->body.shape->GetType() == Shape::aabb)
//	{
//		if (b->body.shape->GetType() == Shape::noCollide)
//		{
//			return false;
//		}
//		else if (b->body.shape->GetType() == Shape::aabb)
//		{
//			return AABBvsAABB(a, b);
//		}
//		else if (b->body.shape->GetType() == Shape::circle)
//		{
//			return AABBvsCircle(a, b);
//		}
//	}
//	else if (a->body.shape->GetType() == Shape::circle)
//	{
//		if (b->body.shape->GetType() == Shape::noCollide)
//		{
//			return false;
//		}
//		else if (b->body.shape->GetType() == Shape::aabb)
//		{
//			return CirclevsAABB(a, b);
//		}
//		else if (b->body.shape->GetType() == Shape::circle)
//		{
//			return CirclevsCircle(a, b);
//		}
//	}
//
//	return false;
//}

bool AABBvsAABB(Object* a, Object* b)
{
	glm::vec3 vAB = b->transform.location - a->transform.location;
	AABB* aShape = reinterpret_cast<AABB*>(a->body.shape);
	AABB* bShape = reinterpret_cast<AABB*>(b->body.shape);

	float xOverlap = aShape->extent.x + bShape->extent.x - glm::abs(vAB.x);
	
	if (xOverlap > 0)
	{
		float yOverlap = aShape->extent.y + bShape->extent.y - glm::abs(vAB.y);

		if (yOverlap > 0)
		{
			float zOverlap = aShape->extent.z + bShape->extent.z - glm::abs(vAB.z);

			if (zOverlap > 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool CirclevsCircle(Object* a, Object* b)
{
	glm::vec3 vAB = b->transform.location - a->transform.location;
	Circle* aShape = reinterpret_cast<Circle*>(a->body.shape);
	Circle* bShape = reinterpret_cast<Circle*>(b->body.shape);

	float radiusSum = aShape->radius + bShape->radius;

	if (vAB.length() < radiusSum)
	{
		return true;
	}

	return false;
}

bool AABBvsCircle(Object* a, Object* b)
{
	glm::vec3 vAB = b->transform.location - a->transform.location;
	AABB* aShape = reinterpret_cast<AABB*>(a->body.shape);
	Circle* bShape = reinterpret_cast<Circle*>(b->body.shape);

	float xOverlap = aShape->extent.x + bShape->radius- glm::abs(vAB.x);

	if (xOverlap > 0)
	{
		float yOverlap = aShape->extent.y + bShape->radius - glm::abs(vAB.y);

		if (yOverlap > 0)
		{
			float zOverlap = aShape->extent.z + bShape->radius - glm::abs(vAB.z);

			if (zOverlap > 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool CirclevsAABB(Object* a, Object* b)
{
	return AABBvsCircle(b, a);
}

bool NoCollision(Object* a, Object* b)
{
	return false;
}