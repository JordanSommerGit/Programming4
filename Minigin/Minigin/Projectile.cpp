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
	m_Sprite->SetSprite("Projectile.png", 50, 50, 12, 8, 8, 0);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
	m_pCollider->SetTrigger(true);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Kinematic);
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
		m_IsDeployed = true;
		m_pRigidbody->SetVelocity(glm::vec3{ 0,-1,0 } * m_FloatSpeed);
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
