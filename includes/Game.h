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
	Logger* m_GameLogger;
	Mario* m_Player;
};

