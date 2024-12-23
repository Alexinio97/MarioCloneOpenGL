#pragma once
#include "Logger.h"
#include "Characters/Mario.h"
#include <box2d/b2_world.h>

class Game
{
public:
	Game(int width, int height, Logger& logger);
	~Game();

	void OnUpdate(float deltaTime);

	void OnRender(float deltaTime);

	inline b2World& GetWorld() const { return *m_World; }

protected:
	int m_Width, m_Height;
	Logger* m_GameLogger;
	Mario* m_Player;
	b2World* m_World;	
};

