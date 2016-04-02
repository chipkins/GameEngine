#pragma once

#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	GLuint getProgram() const;

	bool loadShaders(const char* vertexFile, const char* fragmentFile);
	GLuint loadShader(const char* file, GLenum shaderType);

private:
	GLuint program;
};