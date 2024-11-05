#include "includes/Shader.h"
#include <typeinfo>
#include <glad/glad.h>
#include <vector>

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



	glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShaderId, 1, &vertexCode, NULL);
	glCompileShader(m_VertexShaderId);

	CheckShaderCompilation(m_VertexShaderId);
	
	glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShaderId, 1, &fragmentCode, NULL);
	glCompileShader(m_FragmentShaderId);

	CheckShaderCompilation(m_FragmentShaderId);

	m_ProgramId = glCreateProgram();
	glAttachShader(m_ProgramId, m_VertexShaderId);
	glAttachShader(m_ProgramId, m_FragmentShaderId);

	// Link our program
	glLinkProgram(m_ProgramId);
}

Shader::~Shader()
{
	glDetachShader(m_ProgramId, m_VertexShaderId);
	glDetachShader(m_ProgramId, m_FragmentShaderId);
	glDeleteProgram(m_ProgramId);
}

void Shader::CheckShaderCompilation(GLuint shader)

{
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint logSize = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> logBuffer(logSize);
		glGetShaderInfoLog(shader, logSize, &logSize, &logBuffer[0]);

		glDeleteShader(shader);		
		throw std::exception("Failed shader compilation: " + shader);
	}
}

void Shader::CheckProgramCompilation(GLuint programId) const
{
	GLint isLinked = 0;

	glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint logSize = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> logBuffer(logSize);
		glGetShaderInfoLog(programId, logSize, &logSize, &logBuffer[0]);

		glDeleteProgram(programId);
		glDeleteShader(m_VertexShaderId);
		glDeleteShader(m_FragmentShaderId);
		throw std::exception("Failed program compilation: " + programId);
	}
}
