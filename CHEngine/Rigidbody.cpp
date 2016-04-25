#include "Rigidbody.h"
#include "Shape.h"

Rigidbody::Rigidbody()
{
}

Rigidbody::Rigidbody(Shape *shape, float density)
{
	this->shape = shape;
	this->shape->ComputeMass(this, density);
}

Rigidbody::~Rigidbody()
{
	//delete shape->body;
	delete shape;
}

void Rigidbody::ApplyForce(float dT)
{
	velocity += (force * invMass) * dT;

	force = glm::vec3();
}