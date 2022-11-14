#pragma once
#include <Texture.h>
#include <map>
#include <vector>
#include <Shader.h>

using namespace std;

class Material
{
public:

	Shader shader;
	vector<GLint> parameterHandlers;
	vector<GLuint> textureHandlers;

	Material() = default;
	Material(const Shader& shader);
	//void AddScalarParam(const GLchar* paramName, const float value);
	void AddTextureParam(const GLchar* paramName, const Texture* texture);
	void Use();
};