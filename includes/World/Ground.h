#include "includes/GameObject.h"
#include "includes/Core/Renderer.h"

#pragma once

class Ground : GameObject {
public:
	Ground(glm::vec2 position, glm::vec2 size);

	// Inherited via GameObject
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltTime, Renderer& renderer) override;
};