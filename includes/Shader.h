#pragma once
#include "Logger.h"
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader() = default;
	Shader(Logger& shaderLogger);
	void Compile(const char* vertexCode, const char* fragmentCode);

	~Shader();
private:
	void CheckShaderCompilation(GLuint shader);
	void CheckProgramCompilation(GLuint programId) const;

private:	
	Logger m_ShaderLogger;

	GLuint m_ProgramId;
	GLuint m_VertexShaderId;
	GLuint m_FragmentShaderId;
};

