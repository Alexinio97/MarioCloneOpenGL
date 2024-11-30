#include "includes/Core/Texture.h"
#include "stb/stb_image.h"

Texture2D::Texture2D(const char* path, Logger& textureLogger)
	: m_Path(path), m_TextureLogger(textureLogger)
{
}

Texture2D::~Texture2D()
{	
}

void Texture2D::GenerateTexture()
{		
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	auto textureData = stbi_load(m_Path, &width, &height, &nrChannels, 0);
	if (textureData)
	{
		glTexImage2D(m_TextureId, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(m_TextureId);
	}
	else {
		m_TextureLogger.LogError("Failed to load texture!", "Texture2D");
	}
	

	stbi_image_free(textureData);
}