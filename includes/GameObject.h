#pragma once

#include <glm/glm/glm.hpp>
#include <string>

class Renderer;

class GameObject {
public:	
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender(float deltTime, Renderer& renderer) = 0;
	virtual void OnCollisionEnter(GameObject& other) {};

	inline auto GetPosition() const -> const glm::vec2 { return m_Position; }
	inline auto SetPosition(glm::vec2 newPosition) { m_Position = newPosition; }	
	inline const glm::vec2 GetSize() const { return m_Size; }
	inline const std::string& GetName() const { return m_Name; }
	inline const std::string& GetTag() const { return m_Tag; }

protected:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	std::string m_Name;
	std::string m_Tag;
};