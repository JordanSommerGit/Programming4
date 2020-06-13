#include "MiniginPCH.h"
#include "Enemy.h"
#include "Character.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteRenderComponent.h"

King::Enemy::Enemy()
	: m_IsBubbled{ false }
	, m_CurrentBubbleTime{ 0.f }
	, m_BubbleTime{ 4.f }
	, m_CurrentPopTime{ 0.f }
	, m_PopTime{ 1.f }
	, m_Speed{ 150 }
	, m_FloatSpeed{ 100 }
	, m_CurrentVelocity{ glm::vec3{-150,0,0} }
{
}

void King::Enemy::Bubble()
{
	m_pRigidbody->SetVelocity(glm::vec3{ 0,-1,0 } *m_FloatSpeed);
	m_IsBubbled = true;
}

void King::Enemy::OnTriggerStay(ColliderComponent* other)
{
	if (m_IsBubbled)
	{
		Character* pCharacter = dynamic_cast<Character*>(other->pGameObject);
		if (pCharacter)
		{
			m_IsPopping = true;
		}
	}
}
