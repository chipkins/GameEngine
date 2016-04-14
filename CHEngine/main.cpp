#include "Engine.h"

int main()
{
	Engine engine = Engine();

	if (!engine.init()) { return -1; }
	if (!engine.bufferModel()) { return -1; }
	
	engine.initObject("Textures/telephone-poll.jpg", glm::vec3(0, -0.75, 1), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.initObject("Textures/wood_planks_old.jpg", glm::vec3(0, -0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.initObject("Textures/wood_texture.jpg", glm::vec3(0, 0.25, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0.25, 1));
	engine.initObject("Textures/pigeon.png", glm::vec3(-0.5, -0.4, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.initObject("Textures/pigeon.png", glm::vec3(0, 0.1, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.initObject("Textures/pigeon.png", glm::vec3(0.5, 0.6, 0), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 1));
	engine.initObject("Textures/shotgun2.png", glm::vec3(0.25, -0.75, 0), glm::vec3(0, 0, 0), glm::vec3(0.25, 0.25, 1));

	if (engine.useShaders())
	{
		engine.gameLoop();
	}

	return 0;
}