#include "Engine.h"
#include <iostream>

using glm::vec2;
using glm::vec3;

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

Engine::Engine()
{
	//inputManager = InputManager(this);
}

Engine::~Engine()
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glDeleteTextures(1, &textures[objs[objNames[i]].texture]);
	}
}

GLFWwindow * Engine::getWindowPtr()
{
	return GLFWwindowPtr;
}

bool Engine::init()
{
	// ----------------------------- Initialize a GLFW Window or Quit -----------------------------
	if (glfwInit() == GL_FALSE) { return false; }

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Chrs' DSA1 Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr) { glfwMakeContextCurrent(GLFWwindowPtr); }
	else
	{
		glfwTerminate();
		return false;
	}

	glfwSetCursorPosCallback(getWindowPtr(), mousePosition);
	glfwSetMouseButtonCallback(getWindowPtr(), mouseClick);
	glfwSetKeyCallback(getWindowPtr(), keyCallback);

	// ----------------------------- Initialize a GLEW or Quit -----------------------------
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool Engine::bufferModel()
{
	// ----------------------------- Test Object -----------------------------

	//Vector holding our vertecies
	std::vector<vec3> locs = { 
		{ 1.0f, 1.0f, 0.0f },	//top-right
		{ -1.0f, 1.0f, 0.0f },	//top-left
		{ -1.0f, -1.0f, 0.0f },	//bottom-left
		{ 1.0f, -1.0f, 0.0f }	//bottom-right
	};	
	std::vector<vec2> uvs = {
		{ 1.0f, 1.0f },	//top-right
		{ 0.0f, 1.0f },	//top-left
		{ 0.0f, 0.0f },	//bottom-left
		{ 1.0f, 0.0f }	//bottom-right
	};

	std::vector<unsigned int> locInds = { 0, 1, 2, 0, 2, 3 }; //Vector that indicates the lines connecting the vertices
	vertCount = locInds.size(); //Number of vertices

											 //Duplicate vertices into a single buffer
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i].loc = locs[locInds[i]];
		vertBufData[i].uv = uvs[locInds[i]];
	}

					//GL creating the buffers internally and giving us the indices
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	//Call to control which array and buffer are active
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//Copies data into currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, //Where to copy to
		sizeof(Vertex) * vertCount, //# of bytes to copy
		&vertBufData[0], //Where to copy from
		GL_STATIC_DRAW); //"hint" to OpenGL

						 //Tell GL what format the information it is recieving is in
	//Attrib Ptr for the Vertex's 'loc' field
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					//Attribute index - 0
		3,					//Number of components (x, y, z)
		GL_FLOAT,			//Type of data
		GL_FALSE,			//Should data be normalized?
		sizeof(Vertex),		//Stride (bytes per vertex)
		0);					//Offset to this attribute
	//Attrib Ptr for the Vertex's 'uv' field
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//Attribute index - 1
		2,						//Number of components (u, v)
		GL_FLOAT,				//Type of data
		GL_FALSE,				//Should data be normalized?
		sizeof(Vertex),			//Stride (bytes per vertex)
		(void*)sizeof(vec3));	//Offset to this attribute

	glBindVertexArray(0);

							//Set window color (only done once) - Cornflower Blue
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

bool Engine::gameLoop()
{
	currentTime = glfwGetTime();
	previousTime = currentTime;
	deltaTime = currentTime - previousTime;

	objs["bullet"].active = false;

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// Update -----------
		previousTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;

		for (int i = 0; i < objNames.size(); i++)
		{
			objs[objNames[i]].Update(deltaTime);
		}

		//Draw -----------
		glClear(GL_COLOR_BUFFER_BIT); //Clear the canvas

									  //Render game objects
		for (int i = 0; i < objNames.size(); i++)
		{
			if (objs[objNames[i]].active)
			{
				glm::mat4 locMat = glm::translate(objs[objNames[i]].transform.location);
				glm::mat4 rotMat = glm::yawPitchRoll(objs[objNames[i]].transform.rotation.x,
										objs[objNames[i]].transform.rotation.y,
										objs[objNames[i]].transform.rotation.z);
				glm::mat4 scaleMat;
				if (objNames[i] == "gun")
				{
					glm::vec3 gunScale = glm::vec3();
					gunScale.x = objs[objNames[i]].transform.scale.x - (mouseLoc.x / 2.0f);
					gunScale.y = objs[objNames[i]].transform.scale.y + ((mouseLoc.y + 1) / 5.0f);
					gunScale.z = 1.0f;
					scaleMat = glm::scale(gunScale);
				}
				else
				{
					scaleMat = glm::scale(objs[objNames[i]].transform.scale);
				}
				objs[objNames[i]].transform.objToWorld = locMat * rotMat * scaleMat;

				glEnableVertexAttribArray(2);
				glUniformMatrix4fv(2, 1, GL_FALSE, &objs[objNames[i]].transform.objToWorld[0][0]);

				glBindVertexArray(vertArr);
				if (textures.size() > 0)
				{
					glBindTexture(GL_TEXTURE_2D, textures[objs[objNames[i]].texture]);
				}
				glDrawArrays(GL_TRIANGLES, 0, vertCount);
				glBindVertexArray(0); //Unbind object after drawing it
			}
		}

		//Swap the front and back buffers (what the screen displays and what GL draws, respectively)
		glfwSwapBuffers(GLFWwindowPtr);

		//Process Input ------------
		keyWasDown = keyIsDown;

		glfwPollEvents();

		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(getWindowPtr(), GL_TRUE);
		}
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1])
		{
			objs["bullet"].body.velocity = glm::vec3();
			objs["bullet"].transform.location = glm::vec3(objs["gun"].transform.location.x - objs["gun"].transform.scale.x, 
													objs["gun"].transform.location.y + objs["gun"].transform.scale.y, 
													objs["gun"].transform.location.z);
			glm::vec3 trajectory =  mouseLoc - objs["bullet"].transform.location;
			objs["bullet"].body.force = glm::normalize(trajectory) * 500.0f;

			objs["bullet"].active = true;
		}
	}

	glfwTerminate();

	return true;
}

void Engine::update()
{

}

bool Engine::useShaders()
{
	if (shaderManager.loadShaders("Shaders/vShader.glsl", "Shaders/fShader.glsl"))
	{
		glUseProgram(shaderManager.getProgram());

		return true;
	}

	return false;
}

void Engine::uploadTexture(char* texFile)
{
	//Load texture from file
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(texFile, 0), texFile);
	if (image == nullptr)
	{
		std::cout << "The texture file could not be loaded." << std::endl;
		return; //Texture failed to load
	}
	
	//Convert image to a 32bit bmp
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image); //Unloads the origional from memory

	GLuint texID = 0;
	glGenTextures(1, &texID); //Generate texture
	if (texID == GL_FALSE)
	{
		return; //Failed to generate texture
	}
	glBindTexture(GL_TEXTURE_2D, texID); //Bind texture

	textures[texFile] = texID;

	//Upload texture to VRAM
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit), //Image width
		FreeImage_GetHeight(image32Bit), //Image height
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit)); //Image Address

	//Set min filter to linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Unload the image from RAM
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Engine::createObject(std::string name, char* texFile, vec3 location, vec3 rotation, vec3 scale)
{
	Transform tran = Transform();
	tran.location = location;
	tran.rotation = rotation;
	tran.scale = scale;

	Rigidbody body = Rigidbody();
	body.mass = 0.0f;
	body.velocity = vec3(0, 0, 0);
	body.force = vec3(0, 0, 0);

	Object obj = Object();
	obj.texture = texFile;
	obj.transform = tran;
	obj.body = body;

	objNames.push_back(name);
	objs[name] = obj;

	uploadTexture(texFile);
}
