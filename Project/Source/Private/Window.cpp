#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <Shader.h>
#include <Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Material.h>

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

vector<glm::vec3> vertices = 
{
	glm::vec3(	- 0.5f, -0.5f, 0.0f	),
	glm::vec3(	0.5f, -0.5f, 0.0f	),
	glm::vec3(	0.0f,  0.5f, 0.0f	)
};
vector<glm::vec2> uvs =
{
	glm::vec2(0.0f, 0.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.5f, 1.0f)
};
vector<glm::vec3> normals =
{
	glm::vec3(1.0f,0.0f,0.0f),
	glm::vec3(0.0f,1.0f,0.0f),
	glm::vec3(0.0f,0.0f,1.0f)
};
vector<glm::vec4> colors =
{
	glm::vec4(1.0f,0.0f,0.0f,1.0f),
	glm::vec4(0.0f,1.0f,0.0f,1.0f),
	glm::vec4(0.0f,0.0f,1.0f,1.0f)
};

int width = 800;
int height = 600;

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Foil", NULL, NULL);
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

	Mesh mesh(vertices, uvs, normals, colors);

#pragma endregion

#pragma region Material Setup

	//Shader Declaration
	Shader shader("../../Bin/Shaders/vsh.glsl", "../../Bin/Shaders/fsh.glsl");

	//Texture Allocation
	Texture kirbyTexture("../../Bin/Assets/Textures/kirbo.png");
	Texture checkerTexture("../../Bin/Assets/Textures/T_CheckerSimple.png");
	Material mat(shader);

	//Texture Bind to Material
	mat.AddTextureParam("mainTex", &kirbyTexture);
	mat.AddTextureParam("overlayTex", &checkerTexture);

#pragma endregion

#pragma region Transforms

	//Matrices
	glm::mat4 meshTransform = glm::mat4(1.0f); //Identity Matrix
	glm::mat4 m;
	{
		//TODO: clean this later
		glm::mat4 meshT = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 meshR = glm::rotate(glm::mat4(1.0f), glm::radians(70.0f), glm::vec3(1, 0, 0));
		glm::mat4 meshS = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
		m = meshT * meshR * meshS;
	}
	glm::mat4 cameraT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 cameraR = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1, 0, 0));
	glm::mat4 v = cameraT * cameraR;

	glm::mat4 p = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	GLuint transHandler = glGetUniformLocation(mat.shader.shaderProgramID, "transform"); //Link handler to shader property

#pragma endregion

#pragma region Render Loop
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		mat.Use();

		//Transformations
		meshTransform = p * v * m;
		glUniformMatrix4fv(transHandler, 1, GL_FALSE, glm::value_ptr(meshTransform));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//If the Render loop has stopped, clean and close.
	glfwTerminate();
	return 0;
#pragma endregion
}
