#include "CameraManager.h"
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

CameraManager::CameraManager()
{
	sens = 0.005f;

	camLoc = { 0, 0, 2 };
	camRot = { 0, 0, 0 };

	rotMat = (mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);

	eye = camLoc;
	center = eye + rotMat * vec3(0, 0, -1);
	up = rotMat * vec3(0, 1, 0);

	zoom = 1.0f;
	width = 800;
	height = 600;
	aspect = (float)width / (float)height;

	screenMode = none;

	fov = 3.14159 * 0.4f / zoom;
	zNear = 0.01f;
	zFar = 1000.0f;

	base::initPhysics(Shape::noCollide, vec3(), vec3(), 1);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update(float dt)
{
	base::Update(dt);
	//__super::Update(dt);
	body.shape;
	//Calculate View Matrix
	mat3 rotMat = (mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	vec3 eye = transform.location;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	lookAtMat = glm::lookAt(eye, center, up);

	//Calculate Perspective Matrix
	perspectiveMat = glm::perspective(fov, aspect, zNear, zFar);

	//Calculate the Camera Matrix
	camera = perspectiveMat * lookAtMat;
	//camera = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
	//glUniformMatrix4fv(3, 1, GL_FALSE, &camera[0][0]);
}