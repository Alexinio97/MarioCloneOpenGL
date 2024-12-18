#pragma once

#include "includes/Shader.h"
#include <typeinfo>
#include <vector>
#include "includes/Logger.h"
#include <stdexcept>
#include <glm/glm/gtc/type_ptr.hpp>

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

	m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShaderId, 1, &vertexCode, NULL);
	glCompileShader(m_VertexShaderId);

	CheckShaderCompilation(m_VertexShaderId);
	
	m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShaderId, 1, &fragmentCode, NULL);
	glCompileShader(m_FragmentShaderId);

	CheckShaderCompilation(m_FragmentShaderId);
	
	m_ProgramId = glCreateProgram();	
	glAttachShader(m_ProgramId, m_VertexShaderId);
	glAttachShader(m_ProgramId, m_FragmentShaderId);

	// Link our program
	glLinkProgram(m_ProgramId);
	CheckProgramCompilation(m_ProgramId);
	glDeleteShader(m_VertexShaderId);
	glDeleteShader(m_FragmentShaderId);
}

void Shader::Use()
{
	glUseProgram(m_ProgramId);
}

void Shader::SetInteger(const char* name, int value)
{
	Use();
	glUniform1i(glGetUniformLocation(m_ProgramId, name), value);
}

void Shader::SetVector3(const char* name, glm::vec3 value)
{
	Use();
	glUniform3f(glGetUniformLocation(m_ProgramId, name), value.x, value.y, value.z);
}

void Shader::SetMatrix4(const char* name, glm::mat4 value)
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name), 1, GL_FALSE, glm::value_ptr(value));
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
		std::string errorLog(logBuffer.begin(), logBuffer.end());
		throw std::runtime_error("Failed shader compilation: %s" + errorLog);
	}
}

void Shader::CheckProgramCompilation(GLuint programId) const
{
	GLint success = 0;

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint logSize = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> logBuffer(logSize);
		glGetShaderInfoLog(programId, logSize, &logSize, &logBuffer[0]);

		glDeleteProgram(programId);
		glDeleteShader(m_VertexShaderId);
		glDeleteShader(m_FragmentShaderId);
		std::string errorMessage = "Failed shader compilation: " + std::string(logBuffer.begin(), logBuffer.end());
		throw std::runtime_error("Failed program compilation: " + errorMessage);
	}
}
