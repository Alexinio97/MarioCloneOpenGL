#pragma once

#include <typeinfo>
#include "includes/Game.h"
#include "includes/Shader.h"
#include "includes/ResourceManager.h"
#include <iostream>
#include <filesystem>
#include "includes/Input/Input.h"
#include <GLFW/glfw3.h>

Game::Game(int width, int height, Logger& logger)
    : m_GameLogger(&logger), m_Width(width), m_Height(height)
{	    
    LoadResources();
    InitializeCoreComponents();         

	m_EnemyManger->InitializeEnemies(*m_World, *m_GameScene, 5, glm::vec2((m_Width / 2) + 80, m_Height / 2), glm::vec2(70.0f, 70.0f), 150.0f);

    m_LevelManager = std::make_unique<LevelManager>(*m_Box2dRenderer, *m_GameScene, *m_World);
    m_LevelManager->ReadLevel("Resources/Levels/1.level");
    m_LevelManager->BuildLevel(*m_Renderer, glm::vec2(0, m_Height / 3));
	m_World->SetContactListener(m_ContactListener.get());
}

void Game::LoadResources()
{
    ResourceManager::LoadShader("Resources/Shaders/sprite.vert.glsl",
        "Resources/Shaders/sprite.frag.glsl",
        "default");
    ResourceManager::LoadShader("Resources/Shaders/text.vert.glsl",
        "Resources/Shaders/text.frag.glsl",
        "text");
    ResourceManager::LoadShader("Resources/Shaders/box-debug.vert.glsl", "Resources/Shaders/box-debug.frag.glsl", "box-debug");

    // Load Textures
    ResourceManager::LoadTexture("Resources/Textures/Characters/mario.png", "mario");
    ResourceManager::LoadTexture("Resources/Textures/World/ground.png", "ground");
    ResourceManager::LoadTexture("Resources/Textures/Characters/owl.png", "owl");
}

void Game::InitializeCoreComponents()
{
    Shader& shader = ResourceManager::GetShader("default");
    Shader& box2dShader = ResourceManager::GetShader("box-debug");
    shader.Use();
    shader.SetInteger("ourTexture", 0);

    Shader& textShader = ResourceManager::GetShader("text");
    textShader.Use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width), 0.0f, static_cast<float>(m_Height), -1.0f, 1.0f);
    textShader.SetMatrix4("projection", projection);
    box2dShader.SetMatrix4("projection", projection);    

    ResourceManager::GetShader("default").SetMatrix4("projection", projection);

    m_World = std::make_unique<b2World>(b2Vec2(0, -5));
    m_GameScene = std::make_unique<GameScene>();
    m_Renderer = std::make_unique<Renderer>(shader);
    m_TextRenderer = std::make_unique<TextRenderer>("Resources/Fonts/elsie/Elsie-Regular.otf", 48, textShader);
    m_Box2dRenderer = std::make_unique<Box2DRenderer>(box2dShader);
    m_Player = std::make_unique<Mario>(ResourceManager::GetTexture("mario"), glm::vec2(m_Width / 2, m_Height / 2), glm::vec2(70.0f, 70.0f), false, AnimState::Idle, *m_World, *m_GameScene, *m_Box2dRenderer);
    m_Camera = std::make_unique<Camera>(*m_Player, ResourceManager::GetShader("default"), box2dShader, (float)m_Width, (float)m_Height);    
    m_EnemyManger = std::make_unique<EnemyManager>(*m_Box2dRenderer);
	m_ContactListener = std::make_unique<CharacterContactListener>();
}

Game::~Game()
{  
    for (auto gameObject : m_GameScene->GetGameObjects())
    {
		m_GameScene->UnregisterGameObject(*gameObject);
    }                	
}

void Game::OnUpdate(float deltaTime)
{	    
    auto &gameObjs = m_GameScene->GetGameObjects();
    for (auto gameObject : gameObjs)
    {
        if (gameObject == nullptr) continue;
        gameObject->OnUpdate(deltaTime);
    }	
    m_Camera->Update(deltaTime);
    
    m_World->Step(deltaTime, 8, 3);
}

void Game::OnRender(float deltaTime)
{    
    for(auto gameObject : m_GameScene->GetGameObjects())
	{        
		gameObject->OnRender(deltaTime, *m_Renderer);        
	}
}
