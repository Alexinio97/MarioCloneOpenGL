#include "includes/Shader.h"
#include <typeinfo>
#include <glad/glad.h>

Shader::Shader(Logger& shaderLogger)
	: m_ShaderLogger(shaderLogger)
{
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	if (vertexCode == NULL || *vertexCode == '\0')
	{
		auto errorMsg = "Vertex code is NULL or empty!";
		m_ShaderLogger.LogError(errorMsg);
		throw std::exception(errorMsg);
	}

	if (fragmentCode == NULL || *fragmentCode == '\0')
	{
		auto errorMsg = "Vertex code is NULL or empty!";
		m_ShaderLogger.LogError(errorMsg);
		throw std::exception(errorMsg);
	}

	glShaderSource(m_VertexShaderId, 1, &vertexCode, NULL);
	glCompileShader(m_VertexShaderId);
}
