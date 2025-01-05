#pragma once

#include <includes/Shader.h>
#include <includes/Core/Texture.h>

class Renderer 
{
public:
	Renderer(Shader& shader);
	~Renderer();

	void Render(const Texture2D& texture, glm::vec2 position, glm::vec2 size);
	void RenderSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size, int spriteIndex, int spriteWidth, int spriteHeight);

private:	
	void SetupQuad();

private:
	GLuint m_VAO, m_VBO, m_EBO;
	Shader m_Shader;
};