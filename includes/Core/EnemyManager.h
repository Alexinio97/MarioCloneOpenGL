#pragma once
#include <vector>
#include <includes/Characters/Owl.h>
#include <memory>


class EnemyManager {
public:
	EnemyManager(Box2DRenderer& box2dRenderer);

	void InitializeEnemies(b2World& world, GameScene& scene, int numEnemies, glm::vec2 startPosition, glm::vec2 size, float spacing);	

private:
	std::vector<std::unique_ptr<Owl>> v_Enemies;
	std::unique_ptr<Box2DRenderer> m_Box2dRenderer;
};