#include <memory>

#include "includes/Characters/Mario.h"

class Camera {

public:
	Camera(Mario& Mario, Shader& Shader, float ScreenWidth, float ScreenHeight);

	void Update(float deltaTime);	

	inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

private:
	void UpdateViewMatrix();

private:
	Mario& m_Mario;
	Shader& m_Shader;
	glm::mat4 m_ViewMatrix;
	glm::vec2 m_Position;
	float m_ScreenWidth;
	float m_ScreenHeight;
};