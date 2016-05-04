#pragma once

//#include "Engine.h"
#include <glm/glm.hpp>

struct Engine;

class InputManager
{
	typedef void(Engine::*boundFunc)(int);

public:
	InputManager();
	InputManager(Engine* engine);
	~InputManager();

	//typedef void(Engine::*boundFunc)(int);

	Engine* engine;
	glm::vec3 mouseXY;
	glm::vec3 mouseInPixels;

	void initInput();
	void setInputFunc(int key, boundFunc func);
	void ProcessInput();
};

