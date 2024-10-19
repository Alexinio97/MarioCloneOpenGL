#pragma once

#include <glm/glm/glm.hpp>

class GameObject {
public:
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender(float deltTime) = 0;

	inline auto GetPosition() const -> const glm::vec2 { return m_Position; }
	inline auto SetPosition(glm::vec2 newPosition) { m_Position = newPosition; }

private:
	glm::vec2 m_Position;
};