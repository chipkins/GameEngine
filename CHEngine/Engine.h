#pragma once

#include <vector>

//OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	bool bufferModel();
	bool gameLoop();

private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr; //holds numbers identifying the array
	GLuint vertBuf; //holds numbers identifying the buffer
	unsigned int vertCount;
};

