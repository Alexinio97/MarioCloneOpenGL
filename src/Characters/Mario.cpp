#include "includes/Characters/Mario.h"
#include "includes/Core/Renderer.h"
#include <glad/glad.h>
#include <includes/Input/Input.h>
#include <GLFW/glfw3.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>

Mario::Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState, b2World& world, GameScene& scene)
	: m_Texture(texture), m_IsFlipped(isFlipped), m_AnimationState(animationState), m_Scene(&scene)
{
	m_Position = position;
	m_Size = size;
	m_Speed = 60.0f;
	m_IsDead = false;

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position.Set(m_Position.x, m_Position.y);
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = 2.0f;
	m_Body = world.CreateBody(&bodyDef);
	b2PolygonShape marioShape;
	b2FixtureDef marioFixtureDef;

	marioShape.SetAsBox(m_Size.x / 2.0f, m_Size.y / 2.0f);
	marioFixtureDef.shape = &marioShape;
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
		vel.x = -50;
	}

	if (Input::GetKey(GLFW_KEY_D))
	{
		vel.x = 50;
	}

	m_Body->SetLinearVelocity(vel);
}

void Mario::OnRender(float deltaTime, Renderer& renderer)
{		
	std::cout << "Position: " + std::to_string(m_Position.x) + ", " + std::to_string(m_Position.y) <<std::endl;
	renderer.RenderSprite(m_Texture, m_Position, m_Size, 0, 200, 200);
}
