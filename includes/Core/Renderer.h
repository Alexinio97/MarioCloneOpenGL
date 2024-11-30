#pragma once

#include <glad/glad.h>

class Texture2D;

class Renderer 
{
public:
	Renderer();
	~Renderer();

	void Render(const Texture2D& texture);

private:
	GLuint m_VAO, m_VBO, m_EBO;

	void SetupQuad();
};