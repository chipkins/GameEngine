#pragma once

#include <glm/glm.hpp>

struct Transform
{
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 objToWorld;
};

struct Rigidbody
{
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	float invMass;

	void ApplyForce(float dT)
	{
		velocity += (force * invMass) * dT;

		force = glm::vec3();
	}
};

class Object
{
public:
	Object();
	~Object();

	Transform transform;
	Rigidbody body;
	char* texture;
	bool active;

	void initPhysics(glm::vec3 v, glm::vec3 f, float m);
	void Update(float dT);

private:

};