#include "includes/Characters/Mario.h"
#include <glad/glad.h>

Mario::Mario(Texture2D& texture)
	: m_Texture(texture)
{
}

Mario::~Mario()
{	
}

void Mario::OnUpdate(float deltaTime)
{
}

void Mario::OnRender(float deltaTime, Renderer& renderer)
{
	renderer.Render(m_Texture);
}
