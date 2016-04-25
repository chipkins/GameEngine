#pragma once

#include <glm/glm.hpp>

struct Shape;

class Rigidbody
{

public:
	Rigidbody();
	Rigidbody(Shape *shape, float density);
	~Rigidbody();

	Shape* shape;
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	float invMass;

	void ApplyForce(float dT);
};

