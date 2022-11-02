#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <Shader.h>
#include <TextureInitializer.h>

/*Questions so far :
*	- Why use * in some declarations? - This accesses the content
*	- Why use & in some declarations? - This is a pointer declaration
*	- What does glfwSwapBuffers do behind the scenes? - Swap buffers for things such as double buffering
*	- what is a const char?
*	- why return -1 in some cases?
*/

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void OnGlfwWindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
float uv[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f
};
float colors[] =
{
	1.0f,0.0f,0.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f
};


int main()
{
#pragma region System Initialization
	// GLFW Initialization and OpenGL setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW Window Initialization
	// ---------------------

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW Window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//glfwSetWindowSizeCallback(window, OnGlfwWindowResizeCallback); //Doesn't seem to work

	// GLAD Initialization
	// -------------------

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}

	//Sets the buffer resolution
	glViewport(0, 0, 800, 600);

	//Populate the callback with the new window size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

#pragma region Mesh Handler

	//Vertex Array Object - Attributes
	GLuint AttributeVAO; //VAO Handler
	glGenVertexArrays(1, &AttributeVAO); //Generate Attribute Array
	glBindVertexArray(AttributeVAO); //VAO Bind is parallel to VBO Bind
	
	//Vertex Buffer Object
	GLuint VertexVBO[3]; //0 = Vertex, 1 = UV, 2 = Color
	glGenBuffers(3, VertexVBO); //Generate Vertex Buffer VBO
	
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBO[0]); //Binds VBO ID to an Array Buffer - All operations will be applied on that buffer until the next bind
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copy vertex position data to buffer. Similar to compute buffer declaration

	//Setup Vertex Attribute for VBO[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(0);

	//UV VBO
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBO[1]); //Binds VBO ID to an Array Buffer - All operations will be applied on that buffer until the next bind
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);  //Copy uv data to buffer.

	//Setup Vertex Attribute for VBO[1]
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(1);

	//Color VBO
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBO[2]); //Binds VBO ID to an Array Buffer - All operations will be applied on that buffer until the next bind
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);  //Copy vertex color data to buffer.

	//Setup Vertex Attribute for VBO[2]
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(2);

#pragma endregion

	//Texture Allocation
	TextureInitializer textureObject("Assets/Textures/kirbo.png", 0);

	Shader meshShader("Shaders/vsh.glsl", "Shaders/fsh.glsl"); //Shader Declaration from Shader.cpp

#pragma region Render Loop
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		textureObject.Use();
		glBindVertexArray(AttributeVAO);
		meshShader.Use();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//If the Render loop has stopped, clean and close.
	glfwTerminate();
	return 0;
#pragma endregion
}
