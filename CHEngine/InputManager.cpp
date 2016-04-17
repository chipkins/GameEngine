#include "InputManager.h"

InputManager::InputManager()
{
}

//InputManager::InputManager(Engine* engine)
//{
//	this->engine = engine;
//
//	glfwSetCursorPosCallback(engine->getWindowPtr(), mousePosition);
//	glfwSetMouseButtonCallback(engine->getWindowPtr(), mouseClick);
//	glfwSetKeyCallback(engine->getWindowPtr(), keyCallback);
//}


InputManager::~InputManager()
{
}

//void InputManager::ProcessInput()
//{
//	keyWasDown = keyIsDown;
//	glfwPollEvents();
//
//	if (keyIsDown[GLFW_KEY_ESCAPE])
//	{
//		glfwSetWindowShouldClose(engine->getWindowPtr(), GL_TRUE);
//	}
//	if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1])
//	{
//	texIndex + 1 < textures.size() ? texIndex++ : texIndex = 0;
//	}
//}
