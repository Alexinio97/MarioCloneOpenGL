#include "includes/GameObject.h"
#include "includes/Core/Renderer.h"
#include "includes/Core/Texture.h"
#include <includes/Core/GameScene.h>
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include "includes/Core/Box2DRenderer.h"

#pragma once

class Ground : public GameObject {
public:
	Ground(glm::vec2 position, glm::vec2 size, Texture2D& texture, b2World& world, GameScene& scene, Box2DRenderer& box2DRenderer);

	// Inherited via GameObject
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltTime, Renderer& renderer) override;
	
	inline void SetPosition(glm::vec2 position) { m_Position = position; }	
private:
	b2PolygonShape* m_Shape;
	b2Body* m_Body;
	Texture2D* m_Texture;
	Box2DRenderer* m_Box2DRenderer;
};