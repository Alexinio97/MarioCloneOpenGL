#include "includes/Characters/Mario.h"
#include "includes/Core/Renderer.h"
#include <glad/glad.h>
#include <includes/Input/Input.h>
#include <GLFW/glfw3.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_draw.h>
#include <iostream>

Mario::Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState, b2World& world, GameScene& scene, Box2DRenderer& box2dRenderer)
	: m_Texture(texture), m_IsFlipped(isFlipped), m_AnimationState(animationState), m_Scene(&scene), m_Box2dRenderer(&box2dRenderer), m_IsRight(true), m_AnimIndex(0), m_AnimTimer(0.0f), m_AnimSpeed(0.1f)
{
	m_Position = position;
	m_Size = size;
	m_Speed = 1000.0f;
	m_IsDead = false;

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position.Set(
		m_Position.x,
		m_Position.y
	);
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = 100.0f;
	m_Body = world.CreateBody(&bodyDef);	
	b2FixtureDef marioFixtureDef;
	m_BodyShape = new b2PolygonShape();

	m_BodyShape->SetAsBox(
		m_Size.x / 2.0f,
		m_Size.y / 2.0f,
		b2Vec2(m_Size.x / 2.0f, m_Size.y / 2.0f),
		0
	);
	marioFixtureDef.shape = m_BodyShape;
	marioFixtureDef.friction = 1.0f;
	marioFixtureDef.density = 1.0f;

	m_Body->CreateFixture(&marioFixtureDef);
	scene.RegisterGameObject(*this);
}

Mario::~Mario()
{	
}

// deltaTime is useful for physics-based acceleration (+=), but for constant speed, it's unnecessary.
void Mario::OnUpdate(float deltaTime)
{
	m_Position = { m_Body->GetPosition().x, m_Body->GetPosition().y };
	b2Vec2 vel = m_Body->GetLinearVelocity();

	m_AnimationState = AnimState::Idle;

	if (Input::GetKey(GLFW_KEY_A))
	{
		vel.x = -m_Speed;
		m_IsRight = false;
		m_AnimationState = AnimState::Running;
	}

	if (Input::GetKey(GLFW_KEY_D))
	{
		m_IsRight = true;
		m_AnimationState = AnimState::Running;
		vel.x = m_Speed;
	}

	if (Input::GetKey(GLFW_KEY_SPACE))
	{
		m_AnimationState = AnimState::Jumping;
		vel.y = 90;
	}	

	m_Body->SetLinearVelocity(vel);

	m_AnimTimer += deltaTime;
	if (m_AnimTimer >= m_AnimSpeed)
	{
		m_AnimTimer = 0.0f;
		SetAnimState();
	}
}

void Mario::OnRender(float deltaTime, Renderer& renderer)
{			
	const auto& bodyTransform = m_Body->GetTransform(); // contains coords in world space

	std::vector<b2Vec2> transformedVertices(m_BodyShape->m_count);
	for (int i = 0; i < m_BodyShape->m_count; ++i)
	{
		auto localVertex = m_BodyShape->m_vertices[i];
		transformedVertices[i] = b2Mul(bodyTransform, localVertex); // convert to world space coordinates
	}

	m_Box2dRenderer->DrawPolygon(transformedVertices.data(), m_BodyShape->m_count, b2Color(1.0f, 0.0f, 0.0f));

	// Flip sprite without shifting its position
	glm::vec2 renderPos = m_Position;
	float flipX = m_IsRight ? 1.0f : -1.0f;

	if (!m_IsRight) // Shift position to compensate for mirroring
	{
		renderPos.x += m_Size.x;
	}
		
	renderer.RenderSprite(m_Texture, renderPos, glm::vec2(m_Size.x * flipX, m_Size.y), m_AnimIndex, 200, 200);
}

void Mario::SetAnimState()
{ 
	switch (m_AnimationState)
	{
	case AnimState::Jumping:
		m_AnimIndex = 1;  // Fixed jump sprite
		break;

	case AnimState::Running:
		// Loop through sprites 2-4
		m_AnimIndex = (m_AnimIndex < 2 || m_AnimIndex >= 4) ? 2 : m_AnimIndex + 1;
		break;

	case AnimState::Idle:
	default:
		m_AnimIndex = 0;  // Idle sprite
		break;
	}
}
