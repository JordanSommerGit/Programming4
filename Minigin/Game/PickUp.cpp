#include "MiniginPCH.h"
#include "PickUp.h"
#include "Character.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

void King::PickUp::OnTriggerStay(ColliderComponent* other)
{
	Character* pCharacter = dynamic_cast<Character*>(other->pGameObject);
	if (pCharacter)
	{
		if (m_IsCollectable)
		{
			Collect();
		}
	}
}

void King::PickUp::Collect()
{
	OnCollect();
	Destroy();
}

void King::PickUp::OnCollect()
{
}
