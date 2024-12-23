#include <includes/Core/GameScene.h>

#pragma once

void GameScene::RegisterGameObject(GameObject& gameObj)
{
	m_GameObjects.push_back(&gameObj);
}

void GameScene::UnregisterGameObject(GameObject& gameObj)
{
	auto it = std::find(m_GameObjects.begin(), m_GameObjects.end(), &gameObj);

	if (it != m_GameObjects.end())
	{
		delete *it;
		m_GameObjects.erase(it);
	}
}


