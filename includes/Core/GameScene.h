#pragma once
#include <includes/GameObject.h>
#include <vector>


class GameScene {

public:

	void RegisterGameObject(GameObject& gameObj);
	void UnregisterGameObject(GameObject& gameObj);

	inline const std::vector<GameObject*>& GetGameObjects() const { return m_GameObjects; }

protected:
	std::vector<GameObject*> m_GameObjects;
};