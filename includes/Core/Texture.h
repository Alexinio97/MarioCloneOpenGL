#pragma once
#include <includes/Logger.h>
#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D() = default;
	Texture2D(const char* path, Logger& textureLogger);
	~Texture2D();

	void GenerateTexture();

	inline GLuint GetTextureId() const { return m_TextureId; }

private:
	Logger m_TextureLogger;
	const char* m_Path;
	GLuint m_TextureId;
};