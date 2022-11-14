#pragma once

#include <Mesh.h>
#include <Material.h>
#include <iostream>

class Renderer
{
public:
	Mesh mesh;
	vector<Material> materials;

	Renderer(const Mesh& mesh,const vector<Material>& materials);
	void Draw();
};

