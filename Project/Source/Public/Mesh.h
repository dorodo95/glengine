#pragma once

#include <SubMesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh
{
public:
	vector<SubMesh> subMeshes;

	Mesh() = default;
	Mesh(const char* path);

	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessSubMesh(aiMesh* nodeMesh, const aiScene* scene);
};

