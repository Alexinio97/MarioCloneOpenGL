#include "includes/Characters/Mario.h"
#include <glad/glad.h>
#include <includes/Input/Input.h>
#include <GLFW/glfw3.h>

Mario::Mario(Texture2D& texture, glm::vec2 position, glm::vec2 size, bool isFlipped, AnimState animationState)
	: m_Texture(texture), m_IsFlipped(isFlipped), m_AnimationState(animationState)
{
	m_Position = position;
	m_Size = size;
	m_Speed = 60.0f;
	m_IsDead = false;
}

Mario::~Mario()
{	
}

void Mario::OnUpdate(float deltaTime)
{
	if (Input::GetKey(GLFW_KEY_A))
	{
		m_Position.x += deltaTime * 50.0f;
	}
}

void Mario::OnRender(float deltaTime, Renderer& renderer)
{	
	renderer.RenderSprite(m_Texture, m_Position, m_Size, 0, 200, 200);
}
