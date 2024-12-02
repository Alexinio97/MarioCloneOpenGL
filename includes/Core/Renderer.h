#pragma once

#include <includes/Shader.h>
#include <includes/Core/Texture.h>

class Renderer 
{
public:
	Renderer(Shader& shader);
	~Renderer();

	void Render(const Texture2D& texture);

private:	

	void SetupQuad();

private:
	GLuint m_VAO, m_VBO, m_EBO;
	Shader m_Shader;
};