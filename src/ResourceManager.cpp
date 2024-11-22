#include "includes/ResourceManager.h"
#include "includes/Logger.h"
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ResourceManager::Shaders;

void ResourceManager::LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* shaderName)
{
    auto shader = loadShaderFromFiles(vertexShaderFile, fragmentShaderFile);
    Shaders[shaderName] = shader;    
}

Shader& ResourceManager::GetShader(const char* shaderName)
{
    return Shaders[shaderName];
}

Shader ResourceManager::loadShaderFromFiles(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    Logger ResourceLogger{};
    std::string vertexCode;
    std::string fragmentcode;
    Logger shaderLogger{};

    try {
        std::ifstream vertexFile(vertexShaderFile);
        std::ifstream fragmentFile(fragmentShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentcode = fShaderStream.str();

        if (vertexCode.empty())
            throw std::exception("Vertex code is empty!");
        if (fragmentcode.empty())
            throw std::exception("Fragment code is empty");

        Shader shader(ResourceLogger);
        shader.Compile(vertexCode.c_str(), fragmentcode.c_str());
        return shader;
    }
    catch (std::exception ex)
    {        
        shaderLogger.LogError("Could not read files!", ex);
        throw;
    }
}
