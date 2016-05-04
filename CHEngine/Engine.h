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
#include "PhysicsManager.h"
#include "CameraManager.h"
#include "Vertex.h"
#include "Object.h"

class Engine
{
public:
	Engine();
	~Engine();

	std::map<char*, GLuint> textures;
	std::map<std::string, Object> objs;
	std::vector<std::string> objNames;
	float currentTime;
	float previousTime;
	float deltaTime;

	GLFWwindow* getWindowPtr();

	bool init();
	bool bufferModel();
	bool gameLoop();
	void update(int keyState);
	bool useShaders();
	void uploadTexture(char* texFile);
	void createObject(std::string name, char* texFile, glm::vec3 location, glm::vec3 rotation, glm::vec3 scale, ScreenMode mode);

private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr; //holds numbers identifying the array
	GLuint vertBuf; //holds numbers identifying the buffer
	unsigned int vertCount;
	ShaderManager shaderManager;
	//PhysicsManager physicsManager;
	InputManager* inputManager;
	CameraManager cameraManager;
	void Quit(int keyState);
	void Fire(int keyState);
	void MoveForward(int keyState);
	void MoveBack(int keyState);
	void MoveRight(int keyState);
	void MoveLeft(int keyState);
	void AimCamera();
};