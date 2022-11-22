#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <Shader.h>
#include <Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Material.h>
#include <Renderer.h>
#include <DebugGrid.h>

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

int width = 1600;
int height = 1200;

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

	GLFWwindow* window = glfwCreateWindow(width, height, "Foil", NULL, NULL);
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
	glViewport(0, 0, width, height);

	//Populate the callback with the new window size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

	glEnable(GL_DEPTH_TEST);

#pragma region Mesh Handler

	Mesh mesh("../../Bin/Assets/Models/Luna.obj");

#pragma endregion

#pragma region Material Setup

	//Shader Declaration
	Shader shader("../../Bin/Shaders/vsh.glsl", "../../Bin/Shaders/fsh.glsl");
	Shader gridShader("../../Bin/Shaders/vsh.glsl", "../../Bin/Shaders/gridFSH.glsl");

	//Texture Allocation
	Texture textureA("../../Bin/Assets/Textures/T_LunaBody_D.png");
	Texture textureB("../../Bin/Assets/Textures/T_LunaHair_D.png");
	Texture textureGrid("../../Bin/Assets/Textures/T_Grid.png");
	
	Material matBody(shader);
	Material matHair(shader);
	Material matGrid(gridShader);

	//Texture Bind to Material
	matBody.AddTextureParam("mainTex", &textureA);
	matHair.AddTextureParam("mainTex", &textureB);
	matGrid.AddTextureParam("mainTex", &textureGrid);

	vector<Material> materialList;
	materialList.push_back(matBody);
	materialList.push_back(matHair);

#pragma endregion

	Renderer renderer(mesh, materialList);
	DebugGrid grid(25, matGrid);


#pragma region Transforms

	//Matrices
	glm::mat4 meshTransform = glm::mat4(1.0f); //Identity Matrix
	
	glm::mat4 cameraT = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -2.0f));
	glm::mat4 cameraR = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 1, 0));
	glm::mat4 v = cameraT * cameraR;

	glm::mat4 p = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);
	GLuint transHandler = glGetUniformLocation(shader.shaderProgramID, "transform"); //Link handler to shader property
	GLuint transHandler2 = glGetUniformLocation(gridShader.shaderProgramID, "transform"); //Link handler to shader property

#pragma endregion

#pragma region Render Loop
	//Render Loop
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);

		renderer.Draw();

		glm::mat4 m;
		{
			//TODO: clean this later
			glm::mat4 meshT = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
			glm::mat4 meshR = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0, 1, 0));
			glm::mat4 meshS = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
			m = meshT * meshR * meshS;
		}

		//Transformations
		meshTransform = p * v * m;
		glUniformMatrix4fv(transHandler, 1, GL_FALSE, glm::value_ptr(meshTransform));


		grid.DrawGridQuad();
		glUniformMatrix4fv(transHandler2, 1, GL_FALSE, glm::value_ptr(meshTransform));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//If the Render loop has stopped, clean and close.
	glfwTerminate();
	return 0;
#pragma endregion
}
