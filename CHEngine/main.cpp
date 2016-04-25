#include "Engine.h"

int main()
{
	Engine engine = Engine();

	if (!engine.init()) { return -1; }
	if (!engine.bufferModel()) { return -1; }
	
	engine.createObject("stallBase", "Textures/telephone-poll.jpg", glm::vec3(0, -0.75, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1), none);
	engine.objs["stallBase"].initPhysics(Shape::noCollide, glm::vec3(), glm::vec3(), 1.0f);
	engine.createObject("stallMid", "Textures/wood_planks_old.jpg", glm::vec3(0, -0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1), none);
	engine.objs["stallMid"].initPhysics(Shape::noCollide, glm::vec3(), glm::vec3(), 1.0f);
	engine.createObject("stallTop", "Textures/wood_texture.jpg", glm::vec3(0, 0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1), none);
	engine.objs["stallTop"].initPhysics(Shape::noCollide, glm::vec3(), glm::vec3(), 1.0f);
	engine.createObject("birdLow", "Textures/pigeon.png", glm::vec3(-0.5, -0.4, 1), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1), bounce);
	engine.objs["birdLow"].initPhysics(Shape::aabb, glm::vec3(0.5, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("birdMid", "Textures/pigeon.png", glm::vec3(0, 0.1, 1), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1), bounce);
	engine.objs["birdMid"].initPhysics(Shape::aabb, glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("birdHigh", "Textures/pigeon.png", glm::vec3(0.5, 0.6, 1), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1), bounce);
	engine.objs["birdHigh"].initPhysics(Shape::aabb, glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("gun", "Textures/shotgun2.png", glm::vec3(0.75, -0.75, 0), glm::vec3(0, 0, 0), glm::vec3(0.25, 0.25, 1), none);
	engine.objs["gun"].initPhysics(Shape::noCollide, glm::vec3(), glm::vec3(), 1.0f);
	engine.createObject("bullet", "Textures/bullet.png", glm::vec3(0.25, -0.5, 1), glm::vec3(0, 0, 0), glm::vec3(0.04, 0.05, 1), destroy);
	engine.objs["bullet"].initPhysics(Shape::circle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	if (engine.useShaders())
	{
		engine.gameLoop();
	}

	return 0;
}