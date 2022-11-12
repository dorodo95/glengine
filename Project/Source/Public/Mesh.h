#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Shader.h>
using namespace std;

class Mesh
{
public:
	vector <glm::vec3> vertices;
	vector <glm::vec2> uvs;
	vector <glm::vec3> normals;
	vector <glm::vec4> colors;

	vector<unsigned int> indices;

	Mesh(vector<glm::vec3> vertices, vector<glm::vec2> uvs, vector<glm::vec3> normals, vector<glm::vec4> colors);
	void Draw(Shader &shader);

private:
	GLuint VAO;		//Vertex Array Object Handler
	GLuint VBO[4];	//Vertex Buffer Object: 0 = Vertex, 1 = UV, 2 = Normal, 3 = Color
	GLuint EBO;		//Element Buffer Object Handler

	void SetupMesh();
};

