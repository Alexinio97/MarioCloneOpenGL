#pragma once
#include <includes/Logger.h>

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

private:
	void GenerateTexture(const char* texturePath);

private:
	Logger* TextureLogger;
};