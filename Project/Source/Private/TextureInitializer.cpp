#include "TextureInitializer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

TextureInitializer::TextureInitializer(const char* texturePath, int textureSlot)
{
	glGenTextures(1, &textureID); //Link handler to texture image
	glActiveTexture(GL_TEXTURE0 + textureSlot); //Enables a Texture Slot
	glBindTexture(GL_TEXTURE_2D, textureID); //Bind Texture
	
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true); //Unflip image
	unsigned char* data = stbi_load(texturePath, &width, &height, &nChannels, 0); //Loads Texture data and populates width, height and color channel info
	
	if (!data)
	{
		std::cout << "ERROR::TEXTURE::FILE_NOT_READ" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //Generate Texture Image
	glGenerateMipmap(GL_TEXTURE_2D); //Generate Mipmaps
	
	//We're done with the buffer data, so unload it
	stbi_image_free(data);

	std::cout << "Successfully Loaded Texture!" << std::endl;

};

void TextureInitializer::Use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}