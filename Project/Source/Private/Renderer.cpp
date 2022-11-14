#include "Renderer.h"

Renderer::Renderer(const Mesh& mesh, const vector<Material>& materials)
{
	this->mesh = mesh;
	this->materials = materials;
	for (int i = 0; i < mesh.subMeshes.size(); i++)
	{
		this->mesh.subMeshes[i].InitializeSubMesh();
	}
}

void Renderer::Draw()
{

	for (int i = 0; i < mesh.subMeshes.size(); i++)
	{
		materials[i].Use();
		glBindVertexArray(mesh.subMeshes[i].VAO);
		//std::cout << "DRAWING:: " << mesh.subMeshes[i].indices.size();
		glDrawElements(GL_TRIANGLES, mesh.subMeshes[i].indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}