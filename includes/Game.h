#pragma once
#include "Logger.h"
class Game
{
public:
	Game(int width, int height, Logger& logger);

	void OnUpdate(float deltaTime);

protected:
	Logger* GameLogger;
};

