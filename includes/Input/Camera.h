#pragma once

#include "includes/Shader.h"
// forward declarations
class Mario;

class Camera {

public:
	Camera(Mario& Mario, Shader& DefaultShader, Shader& DebugShader, float ScreenWidth, float ScreenHeight);

	void Update(float deltaTime);	

	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

private:
	void UpdateViewMatrix();

private:
	Mario& m_Mario;
	Shader& m_DefaultShader;
	std::unique_ptr<Shader> m_DebugShader;
	glm::mat4 m_ViewMatrix;
	glm::vec2 m_Position;
	float m_ScreenWidth;
	float m_ScreenHeight;
};