#include "includes/Core/EnemyManager.h"
#include <includes/ResourceManager.h>

EnemyManager::EnemyManager(Box2DRenderer& box2dRenderer)
	: m_Box2dRenderer(&box2dRenderer)
{

}

void EnemyManager::InitializeEnemies(b2World& world, GameScene& scene, int numEnemies, glm::vec2 startPosition, glm::vec2 size, float spacing)
{
	for(int i =0; i < numEnemies; ++i)
	{
		glm::vec2 position = startPosition + glm::vec2(i * spacing, 0.0f);
		v_Enemies.push_back(std::make_unique<Owl>(ResourceManager::GetTexture("owl"), position, glm::vec2(70, 70.0f), world, scene, *m_Box2dRenderer));
	}
}
