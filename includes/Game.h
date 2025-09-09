#pragma once

#include <memory>
#include <box2d/b2_world.h>
#include "Logger.h"
#include "Characters/Mario.h"
#include "includes/Core/GameScene.h"
#include "includes/Core/Renderer.h"
#include "includes/World/Ground.h"
#include "includes/Core/Box2DRenderer.h"
#include "includes/Characters/Owl.h"
#include <includes/World/LevelManager.h>
#include <includes/Input/Camera.h>
#include "includes/Core/TextRenderer.h"
#include "includes/Core/EnemyManager.h"
#include "Collision/CharacterContactListener.h"

class Game
{
public:
	Game(int width, int height, Logger& logger);
	void LoadResources();
	void InitializeCoreComponents();
	~Game();

	void OnUpdate(float deltaTime);

	void OnRender(float deltaTime);

	inline b2World& GetWorld() const { return *m_World; }

protected:
	int m_Width, m_Height;
	std::unique_ptr<Logger> m_GameLogger;

protected:	
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<TextRenderer> m_TextRenderer;
	std::unique_ptr<GameScene> m_GameScene;
	std::unique_ptr<Box2DRenderer> m_Box2dRenderer;
	std::unique_ptr<LevelManager> m_LevelManager;
	std::unique_ptr<Camera> m_Camera;
	std::unique_ptr<b2World> m_World;
	std::unique_ptr<Mario> m_Player;
	std::unique_ptr<EnemyManager> m_EnemyManger;
	std::unique_ptr<CharacterContactListener> m_ContactListener;
};

