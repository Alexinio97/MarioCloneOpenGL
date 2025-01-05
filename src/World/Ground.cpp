#include "includes/World/Ground.h"
#include <box2d/b2_fixture.h>
#include "includes/Core/Box2DRenderer.h"

Ground::Ground(glm::vec2 position, glm::vec2 size, int numTiles, Texture2D& texture, b2World& world, GameScene& scene, Box2DRenderer& box2DRenderer)
	: m_Texture(&texture), m_NumTiles(numTiles), m_Box2DRenderer(&box2DRenderer)
{
	m_Position = position;
	m_Size = size;	

	b2BodyDef bodyDef;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	bodyDef.position.Set(
		m_Position.x + (m_Size.x * m_NumTiles) / 2.0f,
		m_Position.y + m_Size.y / 2.0f
	);
	m_Body = world.CreateBody(&bodyDef);
	b2FixtureDef fixtureDef;
	m_Shape = new b2PolygonShape();

	float halfWidth = (m_Size.x * m_NumTiles) / 2.0f;
	float halfHeight = m_Size.y / 2.0f;               
	m_Shape->SetAsBox(halfWidth, halfHeight);
	fixtureDef.shape = m_Shape;
		
	m_Body->CreateFixture(&fixtureDef);

	scene.RegisterGameObject(*this);
}

void Ground::OnUpdate(float deltaTime)
{

}

void Ground::OnRender(float deltTime, Renderer& renderer)
{	
	const b2Transform& transform = m_Body->GetTransform(); // Get the body's transform	

	std::vector<b2Vec2> transformedVertices(m_Shape->m_count);
	for (int i = 0; i < m_Shape->m_count; ++i)
	{
		const b2Vec2& localVertex = m_Shape->m_vertices[i];
		transformedVertices[i] = b2Mul(transform, localVertex);		
	}

	m_Box2DRenderer->DrawPolygon(transformedVertices.data(), m_Shape->m_count, b2Color(1, 1, 1));
	for (int i = 0; i < m_NumTiles; i++)
	{		
		glm::vec2 pos = glm::vec2(m_Position.x + (i * m_Size.x), m_Position.y);
		renderer.RenderSprite(*m_Texture, pos, m_Size, 0, m_Texture->GetWidth(), m_Texture->GetHeight());
	}
}
