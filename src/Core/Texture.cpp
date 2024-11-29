#include "includes/Core/Texture.h"
#include "stb/stb_image.h"
#include <glad/glad.h>

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	delete TextureLogger;
}

void Texture2D::GenerateTexture(const char* texturePath)
{	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	auto textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (textureData)
	{
		glTexImage2D(textureId, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(textureId);
	}
	else {
		TextureLogger->LogError("Failed to load texture!", "Texture2D");
	}
	

	stbi_image_free(textureData);
}
