#include <typeinfo>
#include "includes/Game.h"
#include <includes/Shader.h>
#include <includes/ResourceManager.h>

Game::Game(int width, int height, Logger& logger)
{
	ResourceManager::LoadShader("sprite.vert.glsl", "sprite.frag.glsl", "basic");
}

void Game::OnUpdate(float deltaTime)
{	
}
