#include <typeinfo>
#include "includes/Game.h"
#include <includes/Shader.h>
#include <includes/ResourceManager.h>
#include <iostream>
#include <filesystem>

Game::Game(int width, int height, Logger& logger)
{
	std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
	ResourceManager::LoadShader("sprite.vert.glsl", "sprite.frag.glsl", "basic");
}

void Game::OnUpdate(float deltaTime)
{	
}
