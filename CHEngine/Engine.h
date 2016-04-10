#pragma once

#include <vector>
#include <map>
#include "ShaderManager.h"

//OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

class Engine
{
public:
	Engine();
	~Engine();

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
	std::map<char*, GLuint> textures;

	ShaderManager shaderManager;
};