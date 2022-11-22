#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include <iostream>

using namespace std;

class SubMesh
{
public:
	vector <glm::vec3> vertices;
	vector <glm::vec2> uvs;
	vector <glm::vec3> normals;
	vector <glm::vec4> colors;
	vector<unsigned int> indices;

	GLuint VAO;		//Vertex Array Object Handler
	GLuint VBO[4];	//Vertex Buffer Object: 0 = Vertex, 1 = UV, 2 = Normal, 3 = Color
	GLuint EBO;		//Element Buffer Object Handler

	SubMesh() = default;
	SubMesh(vector<glm::vec3> vertices, vector<unsigned int> indices, vector<glm::vec2> uvs, vector<glm::vec3> normals, vector<glm::vec4> colors);
	void InitializeSubMesh();

};

