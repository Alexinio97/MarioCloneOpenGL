#pragma once

#include "includes/Core/Texture.h"
#include "includes/GameObject.h"
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include "includes/Core/GameScene.h"

enum AnimState {
	Idle,
	Running
};

class Mario : public GameObject
{
public:
	Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState, b2World& world, GameScene& scene);
	~Mario();
	
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltaTime, Renderer& renderer) override;


private:
	b2Body* m_Body;
	Texture2D m_Texture;
	AnimState m_AnimationState;
	GameScene* m_Scene;
	bool m_IsFlipped;
	float m_Speed;
	bool m_IsDead;
};

