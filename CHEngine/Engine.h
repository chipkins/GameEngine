#pragma once

//OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

#include <vector>
#include <map>
#include "ShaderManager.h"
#include "InputManager.h"
#include "Vertex.h"
#include "Object.h"

class Engine
{
public:
	Engine();
	~Engine();

	std::map<char*, GLuint> textures;
	std::vector<Object> objs;
	float currentTime;
	float previousTime;
	float deltaTime;

	GLFWwindow* getWindowPtr();

	bool init();
	bool bufferModel();
	bool gameLoop();
	bool useShaders();
	void uploadTexture(char* texFile);
	void initObject(char* texFile, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale);

private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr; //holds numbers identifying the array
	GLuint vertBuf; //holds numbers identifying the buffer
	unsigned int vertCount;
	ShaderManager shaderManager;
	InputManager inputManager;
};