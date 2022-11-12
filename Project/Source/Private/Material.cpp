#include "Material.h"

Material::Material(const Shader& shader)
{
	this-> shader = shader;
}

void Material::AddTextureParam(const GLchar* paramName, const Texture* texture)
{
	GLint test = glGetUniformLocation(shader.shaderProgramID, paramName);
	parameterHandlers.push_back(test);
	textureHandlers.push_back(texture->textureID);

	cout << "Added " << paramName << ": " << test << " for ID: " << texture->textureID << '\n';
}

//void Material::AddScalarParam(const GLchar* paramName, float value)
//{
//	GLuint scalarHandle = glGetUniformLocation(shader.shaderProgramID, paramName);
//	scalarParams.emplace(scalarHandle, value);
//}

void Material::Use()
{

	for(int i = 0; i < textureHandlers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); //Enables a Texture Slot
		glBindTexture(GL_TEXTURE_2D, textureHandlers[i]);
		//cout << "activating slot " << i << " for texture bind in handler " << textureHandlers[i] << '\n';
	}

	shader.Use();

	for (int i = 0; i < textureHandlers.size(); i++)
	{
		glUniform1i(parameterHandlers[i], i);
	}
}