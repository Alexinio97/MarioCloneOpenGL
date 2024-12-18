#pragma once

#include "includes/Core/Texture.h"
#include "includes/Core/Renderer.h"
#include "includes/GameObject.h"
#include <box2d/b2_body.h>

enum AnimState {
	Idle,
	Running
};

class Mario : public GameObject
{
public:
	Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState);
	~Mario();
	
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltaTime, Renderer& renderer) override;


private:
	b2BodyDef m_PhysicsBody;
	Texture2D m_Texture;
	AnimState m_AnimationState;
	bool m_IsFlipped;
	float m_Speed;
	bool m_IsDead;
};

