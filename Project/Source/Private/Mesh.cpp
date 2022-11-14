#include "Mesh.h"

Mesh::Mesh(const char* path)
{
	//Load Mesh File
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ASIMP ERROR: " << importer.GetErrorString() << endl;
		return; //Failed to load file, abort
	}

	std::cout << "Successfully loaded Model at " << path << endl;

	//Get Submeshes from node
	ProcessNode(scene->mRootNode, scene);
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene)
{
	std::cout << "No. Children: " << node->mNumChildren << endl;
	std::cout << "No. Total Meshes: " << scene->mNumMeshes << endl;

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		std::cout << "Child: " << node->mChildren[i]->mName.C_Str() << endl;
		std::cout << "No. Meshes: " << node->mChildren[i]->mNumMeshes << endl;

		for (unsigned int j = 0; j < node->mChildren[i]->mNumMeshes; j++)
		{
			//aiMesh* subMesh = scene->mMeshes[node->mMeshes[j]];
			aiMesh* subMesh = scene->mMeshes[node->mChildren[i]->mMeshes[j]];

			std::cout << "Processing submesh at " << subMesh << endl << "---" << endl;

			ProcessSubMesh(subMesh, scene);
		}
	}
}

void Mesh::ProcessSubMesh(aiMesh* nodeMesh, const aiScene* scene)
{
	SubMesh subMesh;
	std::cout << "No. of Vertices: "	<< nodeMesh->mNumVertices << endl;
	std::cout << "No. of UVs: "			<< nodeMesh->mTextureCoords << endl;
	std::cout << "No. of Colors: "	<< nodeMesh->GetNumColorChannels() << endl;

	for (unsigned int i = 0; i < nodeMesh->mNumVertices; i++)
	{
		glm::vec4 vector4;
		glm::vec3 vector3;
		glm::vec2 vector2;

		vector3.x = nodeMesh->mVertices[i].x;
		vector3.y = nodeMesh->mVertices[i].y;
		vector3.z = nodeMesh->mVertices[i].z;
		subMesh.vertices.push_back(vector3);
		vector3 = glm::vec3{ 0,0,0 };

		vector2.x = nodeMesh->mTextureCoords[0][i].x;
		vector2.y = nodeMesh->mTextureCoords[0][i].y;
		subMesh.uvs.push_back(vector2);

		vector3.x = nodeMesh->mNormals[i].x;
		vector3.y = nodeMesh->mNormals[i].y;
		vector3.z = nodeMesh->mNormals[i].z;
		subMesh.normals.push_back(vector3);

		//vector4.r = nodeMesh->mColors[i]->r;
		//vector4.g = nodeMesh->mColors[i]->g;
		//vector4.b = nodeMesh->mColors[i]->b;
		//vector4.a = nodeMesh->mColors[i]->a;
		//subMesh.normals.push_back(vector4);
	}

	std::cout << "Number of Faces: " << nodeMesh->mNumFaces << endl;

	for (unsigned int i = 0; i < nodeMesh->mNumFaces; i++)
	{
		aiFace face = nodeMesh->mFaces[i];
		//std::cout << "Number of Indices: " << face.mNumIndices << endl;

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			subMesh.indices.push_back(face.mIndices[j]);
		}
	}

	subMeshes.push_back(subMesh);
}