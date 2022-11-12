#include "Mesh.h"

Mesh::Mesh(vector<glm::vec3> vertices, vector<glm::vec2> uvs, vector<glm::vec3> normals, vector<glm::vec4> colors)
{
	this->vertices = vertices;
	this->uvs = uvs;
	this->normals = normals;
	this->colors = colors;

	SetupMesh();
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO); //Generate Attribute Array
	glBindVertexArray(VAO);		//VAO Bind is parallel to VBO Bind

	glGenBuffers(4, VBO);		//Generate Vertex Buffer VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); //Binds VBO ID to an Array Buffer - All operations will be applied on that buffer until the next bind
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW); //Copy vertex position data to buffer. Similar to compute buffer declaration

	//Setup Vertex Attribute for VBO[0]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(0);

	//UV VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), uvs.data(), GL_STATIC_DRAW);			//Copy uv data to buffer.

	//Setup Vertex Attribute for VBO[1]
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(1);

	//Normal VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);	//Copy vertex normal data to buffer.

	//Setup Vertex Attribute for VBO[3]
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(2);

	//Color VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), colors.data(), GL_STATIC_DRAW);		//Copy vertex color data to buffer.

	//Setup Vertex Attribute for VBO[3]
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(3);
}
