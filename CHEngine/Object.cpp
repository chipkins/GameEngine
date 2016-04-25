#include "Object.h"

Object::Object()
{
	active = true;
}

Object::~Object()
{

}

void Object::initPhysics(Type type, glm::vec3 v, glm::vec3 f, float d)
{
	Shape* shape = new Shape();
	if (type == aabb)
	{
		glm::vec3 min = transform.location - transform.scale;
		glm::vec3 max = transform.location + transform.scale;
		shape = new AABB(min, max);
	}
	else if (type == circle)
	{
		float radius = transform.scale.y;
		shape = new Circle(radius);
	}
	body.shape = shape;
	body.shape->ComputeMass(&body, d);

	body.velocity = v;
	body.force = f;
}

void Object::Update(float dT)
{
	if (active)
	{
		body.ApplyForce(dT);

		transform.location += body.velocity * dT;

		if (screenMode == wrap)
		{
			ScreenWrap();
		}
		else if (screenMode == bounce)
		{
			ScreenBounce();
		}
		else if (screenMode == destroy)
		{
			ScreenDestroy();
		}
	}
}

void Object::ScreenWrap()
{
	if (transform.location.x >= 1)
	{
		transform.location.x += -2 + transform.location.x;
	}
	if (transform.location.x <= -1)
	{
		transform.location.x += 2 + transform.location.x;
	}
	if (transform.location.y >= 1)
	{
		transform.location.y += -2 + transform.location.y;
	}
	if (transform.location.y <= -1)
	{
		transform.location.y = 2 + transform.location.y;
	}
}

void Object::ScreenBounce()
{
	if (transform.location.x >= 1)
	{
		body.velocity.x *= -1;
		transform.location.x += (transform.location.x - 1) - 0.01;
	}
	if (transform.location.x <= -1)
	{
		body.velocity.x *= -1;
		transform.location.x += (-1 - transform.location.x) + 0.01;
	}
	if (transform.location.y >= 1)
	{
		body.velocity.y *= -1;
		transform.location.y += (transform.location.y - 1) - 0.01;
	}
	if (transform.location.y <= -1)
	{
		body.velocity.y *= -1;
		transform.location.y += (-1 - transform.location.y) + 0.01;
	}
}

void Object::ScreenDestroy()
{
	if (transform.location.x >= 1)
	{
		active = false;
	}
	if (transform.location.x <= -1)
	{
		active = false;
	}
	if (transform.location.y >= 1)
	{
		active = false;
	}
	if (transform.location.y <= -1)
	{
		active = false;
	}
}
