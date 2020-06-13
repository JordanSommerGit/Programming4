#include "MiniginPCH.h"
#include "Zenchan.h"
#include "SpriteRenderComponent.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include <SDL.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "Time.h"
#include "Character.h"

King::Zenchan::Zenchan()
	: m_Speed{ 150 }
	, m_FloatSpeed{ 100 }
	, m_CurrentVelocity{ glm::vec3{-150,0,0} }
	, m_CurrentPopTime{ 0.f }
	, m_PopTime{ 1.f }
{
}

void King::Zenchan::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Enemies.png", 50, 50, 27, 8, 8, 0);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	AddComponent(m_pRigidbody);
}

void King::Zenchan::EarlyUpdate()
{
}

void King::Zenchan::Update()
{
	if (m_pRigidbody->GetVelocity().x == 0.f)
	{
		m_CurrentVelocity.x = -m_CurrentVelocity.x;
	}

	if (m_IsBubbled)
	{
		m_Sprite->SetStartRow(9);
		m_pRigidbody->SetVelocity(glm::vec3{ 0,-1,0 } * m_FloatSpeed);
		m_pCollider->SetTrigger(true);

		if (m_IsPopping)
		{
			if (m_CurrentPopTime < m_PopTime)
			{
				m_CurrentPopTime += Time::GetInstance().GetElapsed();
				m_Sprite->SetStartRow(25);
				m_Sprite->SetFrameCount(24);
				m_Sprite->SetAnimationTime(0.01f);
			}
			if (m_Sprite->GetFrameIndex() == 23)
			{
				Destroy();
			}
		}
	}
	else
	{
		m_pRigidbody->SetVelocity(m_CurrentVelocity);
		if (m_CurrentVelocity.x > 0)
		{
			m_Sprite->SetStartRow(7);
		}
		else
		{
			m_Sprite->SetStartRow(8);
		}
	}
}

void King::Zenchan::Render() const
{
}

void King::Zenchan::OnTriggerStay(ColliderComponent* other)
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
