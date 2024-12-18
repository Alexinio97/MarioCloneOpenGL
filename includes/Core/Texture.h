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
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	int m_Width, m_Height;
	Logger m_TextureLogger;
	const char* m_Path;
	GLuint m_TextureId;
};