#include "includes/Shader.h"
#include <typeinfo>

Shader::Shader(Logger& shaderLogger)
	: ShaderLogger(shaderLogger)
{
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	ShaderLogger.LogInformation("Compiling!", typeid(*this).name());
}
