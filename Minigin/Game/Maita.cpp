#include "MiniginPCH.h"
#include "Maita.h"
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
#include "FrenchFries.h"
#include "Scene.h"
#include "Transform.h"
#include "EventSystem.h"

King::Maita::Maita()
{
}

void King::Maita::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Enemies.png", 40, 40, 27, 8, 8, 0);
	AddComponent(m_Sprite);

	GameObject* pSubCollider = new GameObject();
	m_pCollider = new ColliderComponent(34, 34);
	pSubCollider->AddComponent(m_pCollider);
	AddChild(pSubCollider);
	pSubCollider->GetTransform()->SetPosition(3, 3, 0);

	m_pCollider = new ColliderComponent(40, 40);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	m_pRigidbody->SetApplyGravity(false);
	AddComponent(m_pRigidbody);

	m_CurrentVelocity.y = -100;
	m_CurrentVelocity.x = -100;

	EventSystem::GetInstance().Notify(this, "ENEMY_SPAWNED");
}

void King::Maita::Update()
{
	if (m_pRigidbody->GetVelocity().x == 0.f)
	{
		m_CurrentVelocity.x = -m_CurrentVelocity.x;
	}
	if (m_pRigidbody->GetVelocity().y == 0.f)
	{
		m_CurrentVelocity.y = -m_CurrentVelocity.y;
	}

	if (m_IsBubbled)
	{
		m_Sprite->SetStartRow(2);
		m_pCollider->SetTrigger(true);
		m_pRigidbody->SetApplyDrag(false);

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
				FrenchFries* pFrenchFries = new FrenchFries();
				GetScene()->Add(pFrenchFries);
				pFrenchFries->GetTransform()->SetPosition(GetTransform()->GetPosition());
				EventSystem::GetInstance().Notify(this, "SCORE_1000");
				EventSystem::GetInstance().Notify(this, "ENEMY_KILLED");
				Destroy();
			}
		}
		else
		{
			if (m_CurrentBubbleTime < m_BubbleTime)
			{
				m_CurrentBubbleTime += Time::GetInstance().GetElapsed();
			}
			else
			{
				m_IsBubbled = false;
				m_CurrentBubbleTime = 0.f;
				m_pCollider->SetTrigger(false);
			}
		}
	}
	else
	{
		m_pRigidbody->SetVelocity(m_CurrentVelocity);
		m_pRigidbody->SetApplyDrag(true);
		if (m_CurrentVelocity.x > 0)
		{
			m_Sprite->SetStartRow(0);
		}
		else
		{
			m_Sprite->SetStartRow(1);
		}
	}
}
