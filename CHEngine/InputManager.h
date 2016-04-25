#pragma once

//#include "Engine.h"
#include <glm/glm.hpp>

struct Engine;

class InputManager
{
public:
	InputManager();
	InputManager(Engine* engine);
	~InputManager();

	Engine* engine;
	glm::vec3 mouseXY;

	void setInput();
	void ProcessInput();
};

