#pragma once

#include "includes/Core/Texture.h"
#include "includes/Core/Renderer.h"
#include "includes/GameObject.h"

class Mario : public GameObject
{
public:
	Mario(Texture2D& texture);
	~Mario();
	
	void OnUpdate(float deltaTime) override;
	void OnRender(float deltaTime, Renderer& renderer) override;


private:
	Texture2D m_Texture;
};

