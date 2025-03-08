#include <iostream>
#include <fstream>
#include <sstream>
#include "includes/World/LevelManager.h"
#include <includes/ResourceManager.h>

LevelManager::LevelManager(Box2DRenderer& box2dRenderer, GameScene& gameScene, b2World& world)
	: m_Box2dRenderer(&box2dRenderer), m_GameScene(&gameScene), m_World(&world), m_Level(0), m_IsCompleted(false)
{
}

void LevelManager::ReadLevel(const std::string levelPath)
{
	std::ifstream file(levelPath);
	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << levelPath << std::endl;
		return;
	}
	std::stringstream fileStream;	
	fileStream << file.rdbuf();

	std::string fileContent = fileStream.str();

	for (int i = 0; i < fileContent.length(); i++)
	{
		m_ObjectsToRender.emplace_back(fileContent[i]);
	}

	file.close();	
}

void LevelManager::BuildLevel(Renderer& renderer, glm::vec2 startingPosition)
{
    auto it = m_ObjectsToRender.begin();	

	for (char obj : m_ObjectsToRender)
	{
		if (obj == '#')
		{
			new Ground(startingPosition, glm::vec2(60.0f, 60.0f), ResourceManager::GetTexture("ground"),
				*m_World, *m_GameScene, *m_Box2dRenderer);
		}
		startingPosition.x += 56.0f;
	}
}
