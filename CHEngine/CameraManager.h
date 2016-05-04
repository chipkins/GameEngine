#pragma once

#include "Object.h"

//struct Camera : Object
//{
//
//};

class CameraManager : public Object
{
public:
	CameraManager();
	~CameraManager();

	float sens;

	//View
	glm::vec3 camLoc;
	glm::vec3 camRot;

	glm::mat3 rotMat;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	glm::mat4 lookAtMat;

	//Perspective
	float zoom;
	int width;
	int height;

	float fov;
	float aspect;
	float zNear;
	float zFar;

	glm::mat4 perspectiveMat;

	glm::mat4 camera;

	void Update(float dt) override;

private:
	//glm::mat4 camera;

	typedef Object base;
};

