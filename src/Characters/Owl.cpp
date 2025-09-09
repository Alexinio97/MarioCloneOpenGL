#include "includes/Characters/Owl.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <iostream>

Owl::Owl(Texture2D& texture, glm::vec2 position, glm::vec2 size, b2World& world, GameScene& scene, Box2DRenderer& box2dRenderer)
	: m_Texture(texture), m_Position(position), m_Size(size), m_IsDead(false), m_IsMoving(true), m_Velocity(60.0f), m_PatrolRange(100.0f), m_PatorlUnit(0.0f), m_IsRight(true), m_AnimTimer(0.0f), m_AnimIndex(0)
{
	scene.RegisterGameObject(*this);
	m_Name = "Owl";
	m_Tag = "Enemy";
	m_Box2dRenderer = &box2dRenderer;

	b2BodyDef bodyDef;
	bodyDef.position.Set(
		position.x,
		position.y
	);
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = 100.0f;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(position.x, position.y);
	m_Body = world.CreateBody(&bodyDef);
	b2FixtureDef owlFixtureDef;

	m_BodyShape = new b2PolygonShape();

	std::cout << "Size: " << m_Size.x << " " << m_Size.y << std::endl;	
	m_BodyShape->SetAsBox(
		m_Size.x / 2.0f,
		m_Size.y / 2.0f - 5.0f,
		b2Vec2(m_Size.x / 2.0f, m_Size.y / 2.0f),
		0
	);

	owlFixtureDef.shape = m_BodyShape;
	owlFixtureDef.friction = 1.0f;
	owlFixtureDef.density = 1.0f;

	m_Body->CreateFixture(&owlFixtureDef);
	m_Body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

Owl::~Owl()
{
}

void Owl::OnUpdate(float deltaTime)
{
	m_Position = { m_Body->GetPosition().x, m_Body->GetPosition().y - 15.0f };

	Animation(deltaTime);
	Movement(deltaTime);
}

void Owl::OnRender(float deltTime, Renderer& renderer)
{
	const auto& bodyTransform = m_Body->GetTransform(); 

	std::vector<b2Vec2> transformedVertices(m_BodyShape->m_count);
	for (int i = 0; i < m_BodyShape->m_count; ++i)
	{
		auto localVertex = m_BodyShape->m_vertices[i];
		transformedVertices[i] = b2Mul(bodyTransform, localVertex);
	}

	m_Box2dRenderer->DrawPolygon(transformedVertices.data(), m_BodyShape->m_count, b2Color(1.0f, 0.0f, 0.0f));
	renderer.RenderSprite(m_Texture, m_Position, m_Size, m_AnimIndex, 30, 30);
}

void Owl::Movement(float deltaTime)
{
	if (m_IsMoving)
	{
		b2Vec2 vel = m_Body->GetLinearVelocity();
		m_PatorlUnit += m_Velocity * deltaTime;

		if (m_PatorlUnit >= m_PatrolRange)
		{
			m_IsRight = !m_IsRight;
			m_PatorlUnit = 0.0f;
		}

		if (m_IsRight)
		{
			vel.x = m_Velocity;
		}
		else
		{
			vel.x = -m_Velocity;
		}

		m_Body->SetLinearVelocity(vel);
	}
}

void Owl::Animation(float deltaTime)
{
	m_AnimTimer += deltaTime;

	if (m_AnimTimer >= 0.5f)
	{		
		m_AnimTimer = 0.0f;
		m_AnimIndex = (m_AnimIndex + 1) % 2;
	}

	if (m_IsDead)
	{
		m_AnimIndex = 2;
	}
}

void Owl::Die()
{
	m_IsDead = true;
	m_Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_Body->SetGravityScale(0.0f);
	m_Body->SetType(b2_staticBody);
	m_Body->SetTransform(m_Body->GetPosition(), 0.0f);
	m_BodyShape->SetAsBox(m_Size.x / 2.0f, m_Size.y / 2.0f - 5.0f, b2Vec2(m_Size.x / 2.0f, m_Size.y / 2.0f), 0);
}
