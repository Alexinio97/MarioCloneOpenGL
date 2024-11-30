#include <typeinfo>
#include "includes/Game.h"
#include <includes/Shader.h>
#include <includes/ResourceManager.h>
#include <iostream>
#include <filesystem>


Renderer* renderer;

Game::Game(int width, int height, Logger& logger)
    : m_GameLogger(&logger)
{	
    ResourceManager::LoadShader("Resources/Shaders/sprite.vert.glsl",
        "Resources/Shaders/sprite.frag.glsl",
        "default");

    ResourceManager::LoadTexture("Resources/Textures/Characters/mario.png", "mario");

    ResourceManager::GetShader("default").Use();
    m_Player = new Mario(ResourceManager::GetTexture("mario"));
    renderer = new Renderer();
}

void Game::OnUpdate(float deltaTime)
{	
}

void Game::OnRender(float deltaTime)
{
    m_Player->OnRender(deltaTime, *renderer);
}
