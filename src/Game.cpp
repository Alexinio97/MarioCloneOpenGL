#pragma once

#include <typeinfo>
#include "includes/Game.h"
#include "includes/Shader.h""
#include "includes/ResourceManager.h"
#include "includes/Core/TextRenderer.h"
#include <iostream>
#include <filesystem>
#include <includes/Input/Input.h>
#include <GLFW/glfw3.h>

Renderer* renderer;
TextRenderer* textRenderer;

Game::Game(int width, int height, Logger& logger)
    : m_GameLogger(&logger), m_Width(width), m_Height(height)
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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    textShader.SetMatrix4("projection", projection);
    glm::mat4 viewMatrix = glm::mat4(1);
    ResourceManager::GetShader("default").SetMatrix4("projection", projection);
    ResourceManager::GetShader("default").SetMatrix4("view", viewMatrix);
    m_Player = new Mario(ResourceManager::GetTexture("mario"), glm::vec2(m_Width / 2, m_Height / 2), glm::vec2(70.0f,70.0f), false, AnimState::Idle);
    renderer = new Renderer(shader);
    textRenderer = new TextRenderer("Resources/Fonts/elsie/Elsie-Regular.otf", 48, textShader);
}

void Game::OnUpdate(float deltaTime)
{	
    m_Player->OnUpdate(deltaTime);
}

void Game::OnRender(float deltaTime)
{    
    m_Player->OnRender(deltaTime, *renderer);    
    if(Input::GetKey(GLFW_KEY_A))
        textRenderer->RenderText("A pressed", 10.0f, 30.0f + 0.5 * 20.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    else
        textRenderer->RenderText("0.5", 10.0f, 30.0f + 0.5 * 20.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
