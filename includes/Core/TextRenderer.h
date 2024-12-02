#pragma once

#include <map>
#include "../Shader.h"


struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	unsigned int Advance; // Offset to advance to next glyph
};

class TextRenderer {
public:
	std::map<char, Character> Characters;
	GLuint VAO, VBO;
	Shader TextShader;

	TextRenderer(const std::string& font, GLuint fontSize, Shader& shader);
	void RenderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
	
private:
	void LoadFont(const std::string& font, GLuint fontSize);
};