#include "DebugGrid.h"

DebugGrid::DebugGrid(unsigned int lineAmount, const Material& material)
{
	//Setup VBO and VAO for grid
	this->lineAmount = lineAmount;
	this->material = material;
	//SetupGridLines();
	gridSubMesh.vertices = gridQuadVertices;
	gridSubMesh.indices = gridQuadIndices;
	gridSubMesh.uvs = gridUVs;
	gridSubMesh.InitializeSubMesh();
}

void DebugGrid::SetupGridLines()
{
	int side;
	float offset;
	float length = 2.75f;
	//X Lines
	for (int i = 0; i < lineAmount; i++)
	{
		side = (i % 2) * 2 - 1;
		offset = ceil((float)i / 2);
		offset *= 0.2f;

		//X
		gridPoints.push_back
		(
			glm::vec3(offset * side, 0.0f, -length)
		);

		gridPoints.push_back
		(
			glm::vec3(offset * side, 0.0f,  length)
		);

		//Z
		gridPoints.push_back
		(
			glm::vec3(-length, 0.0f, offset * side)
		);

		gridPoints.push_back
		(
			glm::vec3( length, 0.0f, offset * side)
		);
	}
}

void DebugGrid::DrawGridQuad()
{
	material.Use();
	glBindVertexArray(gridSubMesh.VAO);
	glDrawElements(GL_TRIANGLES, gridSubMesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DebugGrid::DrawGridLines()
{
	material.Use();

	//Axis Lines
	glBindVertexArray(gridSubMesh.VAO);
	for (int i = 0; i < 2; i++)
	{
		glDrawArrays(GL_LINES, i * 2, 2);
	}

	//General Lines
	for (int i = 2; i < lineAmount * 2; i++)
	{
		glDrawArrays(GL_LINES, i * 2, 2);
	}
	glBindVertexArray(0);
}