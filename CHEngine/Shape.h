#pragma once

#include "Rigidbody.h"
#include "Vertex.h"

enum Type
{
	aabb,
	circle,
	noCollide
};

struct Shape
{
	const Type type = noCollide;
	//Rigidbody* body;
	Shape() {}
	virtual Shape* Clone() { return new Shape; }
	virtual void ComputeMass(Rigidbody* body, float density)
	{
		body->mass = 0.0f;
		body->invMass = 0.0f;
	}
	virtual Type GetType() const
	{
		return noCollide;
	}
};

struct AABB : Shape
{
	const Type type = aabb;
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 extent;

	AABB(glm::vec3 min, glm::vec3 max)
	{
		extent = (max - min) / 2.0f;
	}

	Shape* Clone() override
	{
		return new AABB(min, max);
	}

	void ComputeMass(Rigidbody* body, float density) override
	{
		float area = (extent.x * extent.y) * 2.0f;
		body->mass = density * area;
		body->invMass = (body->mass != 0.0f) ? 1.0f / body->mass : 0.0f;
	}

	Type GetType() const override
	{
		return aabb;
	}
};

struct Circle : Shape
{
	const Type type = circle;
	float radius;

	Circle(float r)
	{
		radius = r;
	}

	Shape* Clone() override
	{
		return new Circle(radius);
	}

	void ComputeMass(Rigidbody* body, float density) override
	{
		float area = 3.14159265f * (radius * radius);
		body->mass = density * area;
		body->invMass = (body->mass != 0) ? 1.0f / body->mass : 0.0f;
	}

	Type GetType() const override
	{
		return circle;
	}
};