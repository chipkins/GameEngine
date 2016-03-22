#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
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

	// ----------------------------- Initialize a GLEW or Quit -----------------------------
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	return true;
}

bool Engine::bufferModel()
{
	// ----------------------------- Test Object -----------------------------

	//Vector holding our vertecies
	std::vector<glm::vec3> locs = { 
		{ 0.9, 0.9, 0 },	//top-right
		{ -0.9, 0.9, 0 },	//top-left
		{ -0.9, -0.9, 0 },	//bottom-left
		{ 0.9, -0.9, 0 } };	//bottom-right

	std::vector<unsigned int> locInds = { 0, 1, 2, 0, 2, 3 }; //Vector that indicates the lines connecting the vertices
	vertCount = locInds.size(); //Number of vertices

											 //Duplicate vertices into a single buffer
	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = locs[locInds[i]];
	}

					//GL creating the buffers internally and giving us the indices
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	//Call to control which array and buffer are active
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//Copies data into currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, //Where to copy to
		sizeof(glm::vec3) * vertCount, //# of bytes to copy
		&vertBufData[0], //Where to copy from
		GL_STATIC_DRAW); //"hint" to OpenGL

						 //Tell GL what format the information it is recieving is in
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					//Attribute index - 0
		3,					//Number of components (x, y, z)
		GL_FLOAT,			//Type of data
		GL_FALSE,			//Should data be normalized?
		sizeof(glm::vec3),	//Stride (bytes per vertex)
		0);					//Offset to this attribute

	glBindVertexArray(0);

							//Set window color (only done once) - Cornflower Blue
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

bool Engine::gameLoop()
{
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// Update -----------

		//Draw -----------
		glClear(GL_COLOR_BUFFER_BIT); //Clear the canvas

									  //Render game objects
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		glBindVertexArray(0); //Unbind object after drawing it

							  //Swap the front and back buffers (what the screen displays and what GL draws, respectively)
		glfwSwapBuffers(GLFWwindowPtr);

		//Process ------------
		glfwPollEvents();
	}

	glfwTerminate();

	return true;
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
