#include <string>
#include <map>
#include <vector>
#include <box2d/b2_world.h>
#include "includes/Core/Box2DRenderer.h"
#include "includes/GameObject.h"
#include "includes/Core/GameScene.h"
#include "Ground.h"


class LevelManager {
public:
	LevelManager(Box2DRenderer& box2dRenderer, GameScene& gameScene, b2World& world);

	void ReadLevel(const std::string levelPath);
	void BuildLevel(Renderer& renderer, glm::vec2 startingPosition);

	int m_Level;
	bool m_IsCompleted;

private:
	Box2DRenderer* m_Box2dRenderer;
	GameScene* m_GameScene;
	b2World* m_World;
	std::vector<char> m_ObjectsToRender;
	int m_NothingWidth;
};

enum GameObjectType
{
	Block, // represented by #
	Nothing,  // represented by .
	Pipe // represented by P
};