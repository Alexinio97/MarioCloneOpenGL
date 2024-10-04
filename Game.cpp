#include <typeinfo>
#include "Game.h"

Game::Game(int width, int height, Logger& logger)
{
}

void Game::OnUpdate(float deltaTime)
{
	GameLogger->LogInformation("Game updating!", typeid(*this).name());
}
