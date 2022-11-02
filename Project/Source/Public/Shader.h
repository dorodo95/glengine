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

	//Constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);

	//activate shader
	void Use();

	//utility uniform functions;
	void setBool	(const std::string name, bool value);
	void setInt		(const std::string name, int value);
	void setFloat	(const std::string name, float value);
};

