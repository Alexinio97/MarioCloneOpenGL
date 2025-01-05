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
	: m_Texture(texture), m_IsFlipped(isFlipped), m_AnimationState(animationState), m_Scene(&scene), m_Box2dRenderer(&box2dRenderer)
{
	m_Position = position;
	m_Size = size;
	m_Speed = 60.0f;
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

void Mario::OnUpdate(float deltaTime)
{
	m_Position = { m_Body->GetPosition().x, m_Body->GetPosition().y };
	b2Vec2 vel = m_Body->GetLinearVelocity();
	if (Input::GetKey(GLFW_KEY_A))
	{
		vel.x = -90;
	}

	if (Input::GetKey(GLFW_KEY_D))
	{
		vel.x = 90;
	}

	if (Input::GetKey(GLFW_KEY_SPACE))
	{
		vel.y = 90;
	}

	m_Body->SetLinearVelocity(vel);
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
	renderer.RenderSprite(m_Texture, m_Position, m_Size, 0, 200, 200);
}
