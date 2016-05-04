#pragma once

#include "Rigidbody.h"
#include "Shape.h"

enum ScreenMode
{
	none,
	wrap,
	bounce,
	destroy
};

struct Transform
{
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 objToWorld;
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
	ScreenMode screenMode;

	void initPhysics(Shape::Type type, glm::vec3 v, glm::vec3 f, float d);
	virtual void Update(float dT);

	void ScreenWrap();
	void ScreenBounce();
	void ScreenDestroy();
};