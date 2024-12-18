#pragma once
#include "Logger.h"
#include "Characters/Mario.h"
class Game
{
public:
	Game(int width, int height, Logger& logger);

	void OnUpdate(float deltaTime);

	void OnRender(float deltaTime);

protected:
	int m_Width, m_Height;
	Logger* m_GameLogger;
	Mario* m_Player;
};

