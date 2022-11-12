#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

class Texture
{
public:
	//Texture Attributes
	GLuint textureID;
	int width, height, nChannels;

	Texture(const char* texturePath);

};

