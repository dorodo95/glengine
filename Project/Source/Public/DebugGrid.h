#pragma once

#include <SubMesh.h>
#include <Material.h>

class DebugGrid
{
public:
	SubMesh gridSubMesh;
	Material material;
	unsigned int lineAmount;
	vector<glm::vec3> gridPoints;
	vector<glm::vec3> gridQuadVertices
	{
		glm::vec3(-50.0f, 0, -50),
		glm::vec3(-50.0f, 0,  50),
		glm::vec3(50, 0,  50),
		glm::vec3(50, 0, -50)
	};
	vector<unsigned int> gridQuadIndices
	{
		0, 1, 2,
		2, 3, 0
	};
	vector<glm::vec2> gridUVs
	{
		glm::vec2(-1.0f, -1.0f),
		glm::vec2(-1.0f,  1.0f),
		glm::vec2(1.0f,  1.0f),
		glm::vec2(1.0f, -1.0f)
	};
	DebugGrid(unsigned int lineAmount, const Material& material);
	void DrawGridLines();
	void DrawGridQuad();

private:
	void SetupGridLines();
};

