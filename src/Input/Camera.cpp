#include "includes/Input/Camera.h"
#include <iostream>
#include <glm/glm/gtx/string_cast.hpp>

Camera::Camera(Mario& Mario, Shader& Shader, float ScreenWidth, float ScreenHeight)
	: m_Mario(Mario), m_Shader(Shader), m_ScreenWidth(ScreenWidth), m_ScreenHeight(ScreenHeight)
{
    m_Position = m_Mario.GetPosition();    
}

void Camera::Update(float deltaTime)
{    	
	m_Position = glm::vec2(m_Mario.GetPosition().x - (m_ScreenWidth / 2), m_Mario.GetPosition().y - (m_ScreenHeight / 2));
    UpdateViewMatrix();    
}

void Camera::UpdateViewMatrix()
{	
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f));	
	m_Shader.SetMatrix4("view", transform);
}

   