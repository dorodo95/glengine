#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// Program ID
	GLuint shaderProgramID;

	Shader() = default;
	//Constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);

	//activate shader
	void Use();
};

