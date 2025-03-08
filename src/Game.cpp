#pragma once

#include <typeinfo>
#include "includes/Game.h"
#include "includes/Shader.h"
#include "includes/ResourceManager.h"
#include "includes/Core/TextRenderer.h"
#include <iostream>
#include <filesystem>
#include "includes/Input/Input.h"
#include <GLFW/glfw3.h>
#include "includes/Core/GameScene.h"
#include "includes/Core/Renderer.h"
#include "includes/World/Ground.h"
#include "includes/Core/Box2DRenderer.h"
#include "includes/Characters/Owl.h"
#include <includes/World/LevelManager.h>

Renderer* renderer;
TextRenderer* textRenderer;
GameScene* gameScene;
Box2DRenderer* box2dRenderer;
LevelManager* levelManager;
 
Game::Game(int width, int height, Logger& logger)
    : m_GameLogger(&logger), m_Width(width), m_Height(height)
{	
    m_World = new b2World(b2Vec2(0, -5));
    gameScene = new GameScene();    

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

    Shader& shader = ResourceManager::GetShader("default");
    Shader& box2dShader = ResourceManager::GetShader("box-debug");
    box2dRenderer = new Box2DRenderer(box2dShader);
    shader.Use();
    shader.SetInteger("ourTexture", 0);

    Shader& textShader = ResourceManager::GetShader("text");
    textShader.Use();    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    textShader.SetMatrix4("projection", projection);
    box2dShader.SetMatrix4("projection", projection);
    box2dShader.SetVector3("color", glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 viewMatrix = glm::mat4(1);
    ResourceManager::GetShader("default").SetMatrix4("projection", projection);
    ResourceManager::GetShader("default").SetMatrix4("view", viewMatrix);
    m_Player = new Mario(ResourceManager::GetTexture("mario"), glm::vec2(m_Width / 2, m_Height / 2), glm::vec2(70.0f,70.0f), false, AnimState::Idle, *m_World, *gameScene, *box2dRenderer);

	auto mushroom = new Owl(ResourceManager::GetTexture("owl"), glm::vec2(m_Width / 2, m_Height / 2), glm::vec2(70, 70.0f), *m_World, *gameScene, *box2dRenderer);    
    renderer = new Renderer(shader);
    textRenderer = new TextRenderer("Resources/Fonts/elsie/Elsie-Regular.otf", 48, textShader);    

    levelManager = new LevelManager(*box2dRenderer, *gameScene, *m_World);
	levelManager->ReadLevel("Resources/Levels/1.level");
    levelManager->BuildLevel(*renderer, glm::vec2(m_Width / 3, m_Height / 3));
}

Game::~Game()
{  
    delete(renderer);
    delete(textRenderer);    
    delete(m_World);

    for (auto gameObject : gameScene->GetGameObjects())
    {
		gameScene->UnregisterGameObject(*gameObject);
    }    
    delete(gameScene);
    delete(box2dRenderer);
	delete(levelManager);
}

void Game::OnUpdate(float deltaTime)
{	
    auto gameObjs = gameScene->GetGameObjects();
    for (auto gameObject : gameObjs)
    {
        if (gameObject == nullptr) continue;
        gameObject->OnUpdate(deltaTime);
    }

    m_World->Step(deltaTime, 8, 3);
}

void Game::OnRender(float deltaTime)
{    
    for(auto gameObject : gameScene->GetGameObjects())
	{        
		gameObject->OnRender(deltaTime, *renderer);        
	}
}
