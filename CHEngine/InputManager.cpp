#include "InputManager.h"
#include "Engine.h"

namespace
{
	glm::vec3 mouseLoc;
	//typedef void(Engine::*boundFunc)(int);
	//std::map<int, boundFunc> keybinds;
	std::map<int, bool> keyIsDown;
	std::map<int, bool> keyWasDown;
	int winWidth;
	int winHeight;

	void mousePosition(GLFWwindow* windowPtr, double x, double y)
	{
		glfwGetWindowSize(windowPtr, &winWidth, &winHeight);
		mouseLoc.x = (x / (winWidth / 2)) - 1;
		mouseLoc.y = -((y / (winHeight / 2)) - 1);
	}
	void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods)
	{
		keyIsDown[button] = action;
	}
	void keyCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
	{
		/*if (keybinds.count(key) != 0)
		{
			(this->*keybinds[key])(action);
		}*/
		keyIsDown[key] = action;
	}
}

InputManager::InputManager()
{
}

InputManager::InputManager(Engine* engine)
{
	this->engine = engine;
}


InputManager::~InputManager()
{
	
}

void InputManager::setInput()
{
	glfwSetCursorPosCallback(engine->getWindowPtr(), mousePosition);
	glfwSetMouseButtonCallback(engine->getWindowPtr(), mouseClick);
	glfwSetKeyCallback(engine->getWindowPtr(), keyCallback);
}

void InputManager::ProcessInput()
{
	keyWasDown = keyIsDown;
	glfwPollEvents();

	mouseXY = mouseLoc;

	if (keyIsDown[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(engine->getWindowPtr(), GL_TRUE);
	}
	if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1])
	{
		engine->objs["bullet"].body.velocity = glm::vec3();
		engine->objs["bullet"].transform.location = glm::vec3(engine->objs["gun"].transform.location.x - engine->objs["gun"].transform.scale.x,
																engine->objs["gun"].transform.location.y + engine->objs["gun"].transform.scale.y,
																engine->objs["gun"].transform.location.z);
		glm::vec3 trajectory = mouseLoc - engine->objs["bullet"].transform.location;
		engine->objs["bullet"].body.force = glm::normalize(trajectory) * 10.0f;

		engine->objs["bullet"].active = true;
	}
}
