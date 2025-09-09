#include "includes/Collision/CharacterContactListener.h"
#include <iostream>
#include <includes/GameObject.h>
#include <includes/Characters/Mario.h>


void CharacterContactListener::BeginContact(b2Contact* contact)
{	
	auto bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	if (bodyUserData)
	{
		auto gameObjA = reinterpret_cast<GameObject*>(bodyUserData);
		if (gameObjA->GetTag() == "Player")
		{
			auto player = static_cast<Mario*>(gameObjA);

			auto bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
			if (bodyUserDataB && player)
			{
				auto gameObjB = reinterpret_cast<GameObject*>(bodyUserDataB);
				if (gameObjB->GetTag() == "Enemy")
				{
					player->OnCollisionEnter(*gameObjB);
				}
			}
		}
	}
}

void CharacterContactListener::EndContact(b2Contact* contact)
{	
}
