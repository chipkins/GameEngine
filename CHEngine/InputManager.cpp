#include "InputManager.h"

namespace
{
	glm::vec2 mouseLoc;
	typedef void(Engine::*boundFunc)(int);
	std::map<int, boundFunc> keybinds;
	std::map<int, bool> keyIsDown;
	std::map<int, bool> keyWasDown;

	void mousePosition(GLFWwindow* windowPtr, double x, double y)
	{
		mouseLoc.x = x;
		mouseLoc.y = y;
	}
	void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods)
	{
		keyIsDown[button] = action;
	}
	void keyCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
	{
		if (keybinds.count(key) != 0)
		{
			(*keybinds[key])(action);
		}
		keyIsDown[key] = action;
	}
}

InputManager::InputManager()
{
}

InputManager::InputManager(Engine* engine)
{
	this->engine = engine;

	glfwSetCursorPosCallback(engine->getWindowPtr(), mousePosition);
	glfwSetMouseButtonCallback(engine->getWindowPtr(), mouseClick);
	glfwSetKeyCallback(engine->getWindowPtr(), keyCallback);
}


InputManager::~InputManager()
{
}

void InputManager::ProcessInput()
{
	keyWasDown = keyIsDown;
	glfwPollEvents();

	if (keyIsDown[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(engine->getWindowPtr(), GL_TRUE);
	}
	/*if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1])
	{
	texIndex + 1 < textures.size() ? texIndex++ : texIndex = 0;
	}*/
}
