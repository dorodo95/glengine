#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class TextureInitializer
{
public:
	//Texture Attributes
	GLuint textureID;
	int width, height, nChannels;

	TextureInitializer(const char* texturePath, int textureSlot);

	void Use();
};

