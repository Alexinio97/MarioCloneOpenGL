#pragma once
#include "Logger.h"

class Shader
{
public:
	Shader() = default;
	Shader(Logger& shaderLogger);
	void Compile(const char* vertexCode, const char* fragmentCode);

private:	
	Logger ShaderLogger;
};

