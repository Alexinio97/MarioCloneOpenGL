#pragma once

#include "includes/Core/Texture.h"
#include "includes/GameObject.h"
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include "includes/Core/GameScene.h"
#include "includes/Core/Box2DRenderer.h"

enum AnimState {
	Idle,
	Running,
	Jumping
};

class Mario : public GameObject
{
public:
	Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState, b2World& world, GameScene& scene, Box2DRenderer& box2dRenderer);
	~Mario();
	
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltaTime, Renderer& renderer) override;
	void OnCollisionEnter(GameObject& other) override;

private:
	void SetAnimState();

private:
	b2Body* m_Body;
	Texture2D m_Texture;
	AnimState m_AnimationState;
	GameScene* m_Scene;
	Box2DRenderer* m_Box2dRenderer;
	b2PolygonShape* m_BodyShape;
	bool m_IsFlipped;
	float m_Speed;
	bool m_IsDead;
	bool m_IsRight;
	int m_AnimIndex;
	float m_AnimTimer;
	float m_AnimSpeed;
};

