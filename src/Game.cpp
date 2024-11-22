#include <typeinfo>
#include "includes/Game.h"
#include <includes/Shader.h>
#include <includes/ResourceManager.h>
#include <iostream>
#include <filesystem>

Game::Game(int width, int height, Logger& logger)
{	
    ResourceManager::LoadShader("Resources/Shaders/sprite.vert.glsl",
        "Resources/Shaders/sprite.frag.glsl",
        "default");

}

void Game::OnUpdate(float deltaTime)
{	
}
