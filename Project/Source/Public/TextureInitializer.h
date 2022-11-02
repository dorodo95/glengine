#pragma once

#include <glad/glad.h>

#include <string>
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

