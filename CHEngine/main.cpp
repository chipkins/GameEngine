#include "Engine.h"

int main()
{
	Engine engine = Engine();

	if (!engine.init()) { return -1; }
	if (!engine.bufferModel()) { return -1; }
	
	engine.createObject("stallBase", "Textures/telephone-poll.jpg", glm::vec3(0, -0.75, 1), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.createObject("stallMid", "Textures/wood_planks_old.jpg", glm::vec3(0, -0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.createObject("stallTop", "Textures/wood_texture.jpg", glm::vec3(0, 0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.createObject("birdLow", "Textures/pigeon.png", glm::vec3(-0.5, -0.4, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.objs["birdLow"].initPhysics(glm::vec3(0.5, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("birdMid", "Textures/pigeon.png", glm::vec3(0, 0.1, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.objs["birdMid"].initPhysics(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("birdHigh", "Textures/pigeon.png", glm::vec3(0.5, 0.6, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.objs["birdHigh"].initPhysics(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(), 1.0f);
	engine.createObject("gun", "Textures/shotgun2.png", glm::vec3(0.75, -0.75, 0), glm::vec3(0, 0, 0), glm::vec3(0.25, 0.25, 1));
	engine.createObject("bullet", "Textures/bullet.png", glm::vec3(0.25, -0.5, 0), glm::vec3(0, 0, 0), glm::vec3(0.04, 0.05, 1));
	engine.objs["bullet"].initPhysics(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	if (engine.useShaders())
	{
		engine.gameLoop();
	}

	return 0;
}