#pragma once
#include "Shader.h"
#include <map>
#include <string>

class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;

	static void LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* shaderName);

	static Shader& GetShader(const char* shaderName);


private:
	ResourceManager() = default;

	static auto loadShaderFromFiles(const char* vertexShaderFile, const char* fragmentShaderFile) -> Shader;
};

