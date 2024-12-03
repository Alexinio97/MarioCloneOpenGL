#pragma once

#include <typeinfo>
#include "includes/Game.h"
#include "includes/Shader.h""
#include "includes/ResourceManager.h"
#include "includes/Core/TextRenderer.h"
#include <iostream>
#include <filesystem>

Renderer* renderer;
TextRenderer* textRenderer;

Game::Game(int width, int height, Logger& logger)
    : m_GameLogger(&logger)
{	
    ResourceManager::LoadShader("Resources/Shaders/sprite.vert.glsl",
        "Resources/Shaders/sprite.frag.glsl",
        "default");
    ResourceManager::LoadShader("Resources/Shaders/text.vert.glsl",
        "Resources/Shaders/text.frag.glsl",
        "text");

    ResourceManager::LoadTexture("Resources/Textures/Characters/mario.png", "mario");

    Shader& shader = ResourceManager::GetShader("default");
    shader.Use();
    shader.SetInteger("ourTexture", 0);

    Shader& textShader = ResourceManager::GetShader("text");
    textShader.Use();    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    textShader.SetMatrix4("projection", projection);

    m_Player = new Mario(ResourceManager::GetTexture("mario"));
    renderer = new Renderer(shader);
    textRenderer = new TextRenderer("Resources/Fonts/elsie/Elsie-Regular.otf", 48, textShader);
}

void Game::OnUpdate(float deltaTime)
{	
}

void Game::OnRender(float deltaTime)
{
    //m_Player->OnRender(deltaTime, *renderer);
    textRenderer->RenderText("Test text for opengl!", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
