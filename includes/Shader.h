#pragma once
#include "Logger.h"
#include <glm.hpp>
#include <glad/glad.h>

class Shader
{
public:
	Shader() = default;
	Shader(Logger& shaderLogger);
	void Compile(const char* vertexCode, const char* fragmentCode);
	void Use();

	void SetInteger(const char* name, int value);
	void SetVector3(const char* name, glm::vec3 value);
	
private:
	void CheckShaderCompilation(GLuint shader);
	void CheckProgramCompilation(GLuint programId) const;

private:	
	Logger m_ShaderLogger;

	GLuint m_ProgramId;
	GLuint m_VertexShaderId;
	GLuint m_FragmentShaderId;
};

