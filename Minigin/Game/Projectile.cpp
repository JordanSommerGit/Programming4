#include "MiniginPCH.h"
#include "Projectile.h"
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
#include "Enemy.h"
#include "Transform.h"

King::Projectile::Projectile(glm::vec3 direction)
	: m_Sprite{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_pCollider{ nullptr }
	, m_Direction{ direction }
	, m_Speed{ 300.f }
	, m_FloatSpeed{ 50.f }
	, m_CurrentDeploymentTime{ 0.f }
	, m_DeploymentTime{ 0.4f }
	, m_CurrentPopTime{ 0.f }
	, m_PopTime{ 1.f }
{
}

void King::Projectile::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Projectile.png", 40, 40, 12, 8, 8, 0);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(40, 40);
	m_pCollider->SetTrigger(true);
	AddComponent(m_pCollider);

	GameObject* pSubCollider = new GameObject();
	m_pCollider = new ColliderComponent(34, 34);
	pSubCollider->AddComponent(m_pCollider);
	AddChild(pSubCollider);
	pSubCollider->GetTransform()->SetPosition(3, 3, 0);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	m_pRigidbody->SetApplyGravity(false);
	m_pRigidbody->SetApplyDrag(false);
	AddComponent(m_pRigidbody);
}

void King::Projectile::EarlyUpdate()
{
}

void King::Projectile::Update()
{
	if (m_CurrentDeploymentTime < m_DeploymentTime)
	{
		m_pRigidbody->SetVelocity(m_Direction * m_Speed);
		m_CurrentDeploymentTime += Time::GetInstance().GetElapsed();
	}
	else
	{
		if (!m_IsDeployed)
		{
			m_pRigidbody->SetVelocity(glm::vec3{ 0,-1,0 } * m_FloatSpeed);
		}
		m_IsDeployed = true;
	}

	if (m_IsPopping)
	{
		if (m_CurrentPopTime < m_PopTime)
		{
			m_CurrentPopTime += Time::GetInstance().GetElapsed();
			m_Sprite->SetStartRow(2);
			m_Sprite->SetFrameCount(24);
			m_Sprite->SetAnimationTime(0.01f);
		}
		if (m_Sprite->GetFrameIndex() == 23)
		{
			Destroy();
		}
	}
}

void King::Projectile::Render() const
{
}

void King::Projectile::ChangeVelocityRandom()
{
	int velX = (int)m_pRigidbody->GetVelocity().x;
	//int velY = m_pRigidbody->GetVelocity().y;

	int random = (rand() % 2) * 2 - 1;
	if (velX != 0)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ 0,random,0 });
	}
	else
	{
		m_pRigidbody->SetVelocity(glm::vec3{ random,0,0 });
	}
}

void King::Projectile::OnTriggerStay(ColliderComponent* other)
{
	if (m_IsDeployed)
	{
		Character* pCharacter = dynamic_cast<Character*>(other->pGameObject);
		if (pCharacter)
		{
			m_IsPopping = true;
		}
	}
	Enemy* pEnemy = dynamic_cast<Enemy*>(other->pGameObject);
	if (pEnemy)
	{
		pEnemy->Bubble();
		Destroy();
	}
}
