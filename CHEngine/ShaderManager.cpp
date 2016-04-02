#include "ShaderManager.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

ShaderManager::ShaderManager()
{
	program = 0;
}

ShaderManager::~ShaderManager()
{
}

GLuint ShaderManager::getProgram() const
{
	return program;
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile)
{
	//Load in shaders
	GLint vShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vShader == GL_FALSE)
	{
		return false;
	}

	GLint fShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fShader == GL_FALSE)
	{
		return false;
	}

	//Create shader program
	program = glCreateProgram();
	
	//Attach shaders to the program
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	//Link the program
	glLinkProgram(program);

	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_TRUE)
	{
		return true;
	}

	GLint length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	GLchar* log = new GLchar[length];
	glGetProgramInfoLog(program, length, 0, log);

	for (int i = 0; i < length; i++)
	{
		cout << *(log + i);
	}
	cout << endl;

	glDeleteProgram(program);
	delete[] log;

	return false;
}

GLuint ShaderManager::loadShader(const char * file, GLenum shaderType)
{
	//Read in shader file
	ifstream inFile(file, ios::binary);
	if (inFile.is_open())
	{
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();
		inFile.seekg(0, ios::beg);

		GLchar* fileContents = new char[length + 1];
		inFile.read(fileContents, length);
		fileContents[length] = 0;

		inFile.close();

		GLuint index = glCreateShader(shaderType); //Create a shader and return its address
		glShaderSource(index, 1, &fileContents, 0); //Give the shader our written program
		glCompileShader(index); //Compile shader
		delete[] fileContents;

		GLint result;
		glGetShaderiv(index, GL_COMPILE_STATUS, &result); //Determine if the compile was successful
		if (result == GL_TRUE)
		{
			return index; //Successfully compiled
		}
		
		//Did not compile
		GLint logLength;
		glGetShaderiv(index, GL_INFO_LOG_LENGTH, &logLength); //Get the length of the output log
		GLchar* log = new GLchar[logLength];
		glGetShaderInfoLog(index, logLength, 0, log); //Get the output log

		for (int i = 0; i < logLength; i++)
		{
			cout << *(log + i);
		}
		cout << endl;

		glDeleteShader(index);
		delete[] log;

		return 0;
	}
	else
	{
		cout << "The shader file " << shaderType << " could not be loaded." << endl;
		return 0;
	}
}
