#pragma once
#include "Shader.h"
#include <map>
#include <string>
#include "Core/Texture.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static void LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* shaderName);

	static Shader& GetShader(const char* shaderName);

	static void LoadTexture(const char* textureFile, const char* name);

	static Texture2D& GetTexture(const char* name);

private:
	ResourceManager() = default;

	static auto loadShaderFromFiles(const char* vertexShaderFile, const char* fragmentShaderFile) -> Shader&;
};

