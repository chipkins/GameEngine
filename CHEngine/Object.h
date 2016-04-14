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
};

struct Object
{
	Transform transform;
	Rigidbody body;
	char* texture;
};