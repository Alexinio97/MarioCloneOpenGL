#include "includes/ResourceManager.h"
#include "includes/Logger.h"
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

void ResourceManager::LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* shaderName)
{
    Shader& shader = loadShaderFromFiles(vertexShaderFile, fragmentShaderFile);
    Shaders[shaderName] = shader;    
}

Shader& ResourceManager::GetShader(const char* shaderName)
{
    return Shaders[shaderName];
}

Texture2D& ResourceManager::GetTexture(const char* textureName)
{
    return Textures[textureName];
}

Shader& ResourceManager::loadShaderFromFiles(const char* vertexShaderFile, const char* fragmentShaderFile)
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

void ResourceManager::LoadTexture(const char* textureFile, const char* name)
{
    Logger ResourceLogger{};
    Texture2D newTexture(textureFile, ResourceLogger);

    newTexture.GenerateTexture();

    Textures[name] = newTexture;
}
