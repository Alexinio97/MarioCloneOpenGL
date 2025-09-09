#pragma once
#include "includes/GameObject.h"
#include <includes/Core/Texture.h>
#include <box2d/b2_world.h>
#include <includes/Core/GameScene.h>
#include "includes/Core/Renderer.h"
#include <includes/Core/Box2DRenderer.h>
 
class Owl : public GameObject
{
public:
	Owl(Texture2D& texture, glm::vec2 position, glm::vec2 size, b2World& world, GameScene& scene, Box2DRenderer& box2dRenderer);
	~Owl();

	// Inherited via GameObject
	void OnUpdate(float deltaTime) override;

	void OnRender(float deltTime, Renderer& renderer) override;

	void Movement(float deltaTime);

	void Animation(float deltaTime);

	void Die();

private:
	Texture2D m_Texture;
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	b2Body* m_Body;
	b2PolygonShape* m_BodyShape;
	Box2DRenderer* m_Box2dRenderer;
	bool m_IsDead;
	bool m_IsMoving;
	float m_Velocity;
	float m_PatrolRange;
	float m_PatorlUnit;
	float m_AnimTimer;
	int m_AnimIndex;
	bool m_IsRight;

// constants
private:
	const float PIXELS_TO_METERS = 12.0f;
};