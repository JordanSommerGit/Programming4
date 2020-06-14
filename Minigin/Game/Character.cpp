#include "MiniginPCH.h"
#include "Character.h"
#include "GameObject.h"
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
#include "Projectile.h"
#include "Scene.h"
#include "Enemy.h"
#include "EventSystem.h"

King::Character::Character()
	: m_Sprite{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_CurrentJumpTime{ 0.4f }
	, m_JumpTime{ 0.4f }
	, m_CurrentSpawnTime{ 0.f }
	, m_SpawnTime{ 0.5f }
	, m_CurrentAttackAnimTime{ 0.3f }
	, m_AttackAnimTime{ 0.3f }
	, m_CurrentAttackCDTime{ 0.5f }
	, m_AttackCDTime{ 0.5f }
	, m_CurrentInvincibleTime{ 2.f }
	, m_InvincibleTime{ 2.f }
{
}

void King::Character::Initialize()
{
	using namespace King;

	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Character.png", 40, 40, 12, 8, 8, 0);
	AddComponent(m_Sprite);

	GameObject* pSubCollider = new GameObject();
	m_pCollider = new ColliderComponent(34, 34);
	pSubCollider->AddComponent(m_pCollider);
	AddChild(pSubCollider);
	pSubCollider->GetTransform()->SetPosition(3, 3, 0);

	m_pCollider = new ColliderComponent(40, 40);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	AddComponent(m_pRigidbody);
}

void King::Character::EarlyUpdate()
{
}

void King::Character::Update()
{
	using namespace King;

	if (m_CurrentSpawnTime < m_SpawnTime)
	{
		m_CurrentSpawnTime += Time::GetInstance().GetElapsed();
		return;
	}

	//Input
	if (InputManager::GetInstance().GetEvent().type == SDL_EventType::SDL_KEYDOWN)
	{
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_D)
		{
			m_DDown = true;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_A)
		{
			m_ADown = true;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_W)
		{
			m_WDown = true;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_F)
		{
			m_FDown = true;
		}
	}

	if (InputManager::GetInstance().GetEvent().type == SDL_EventType::SDL_KEYUP)
	{
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_D)
		{
			m_DDown = false;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_A)
		{
			m_ADown = false;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_W)
		{
			m_WDown = false;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_F)
		{
			m_FDown = false;
		}
	}

	//Animation
	if (m_LookingRight)
	{
		if (m_CurrentAttackAnimTime < m_AttackAnimTime)
		{
			m_Sprite->SetStartRow(2);
		}
		else
		{
			m_Sprite->SetStartRow(0);
		}
	}
	else
	{
		if (m_CurrentAttackAnimTime < m_AttackAnimTime)
		{
			m_Sprite->SetStartRow(4);
		}
		else
		{
			m_Sprite->SetStartRow(1);
		}
	}

	//Movement
	if (m_DDown)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ 150,m_pRigidbody->GetVelocity().y,0 });
		m_LookingRight = true;
	}
	if (m_ADown)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ -150,m_pRigidbody->GetVelocity().y,0 });
		m_LookingRight = false;
	}
	if (m_WDown)
	{
		if (m_pRigidbody->IsColliding() && m_CurrentJumpTime >= m_JumpTime)
		{
			m_CurrentJumpTime = 0.f;
		}
	}
	if (m_FDown && m_CurrentAttackCDTime >= m_AttackCDTime)
	{
		Projectile* pProjectile;
		if (m_LookingRight)
		{
			pProjectile = new Projectile(glm::vec3{ 1,0,0 });
		}
		else
		{
			pProjectile = new Projectile(glm::vec3{ -1,0,0 });
		}
		GetScene()->Add(pProjectile);
		pProjectile->GetTransform()->SetPosition(this->GetTransform()->GetPosition());

		m_CurrentAttackCDTime = 0.f;
		m_CurrentAttackAnimTime = 0.f;
	}

	//Cooldowns
	if (m_CurrentJumpTime < m_JumpTime)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ m_pRigidbody->GetVelocity().x, -300, 0 });
		m_CurrentJumpTime += Time::GetInstance().GetElapsed();
	}
	if (m_CurrentAttackAnimTime < m_AttackAnimTime)
	{
		m_CurrentAttackAnimTime += Time::GetInstance().GetElapsed();
	}
	if (m_CurrentAttackCDTime < m_AttackCDTime)
	{
		m_CurrentAttackCDTime += Time::GetInstance().GetElapsed();
	}
	if (m_CurrentInvincibleTime < m_InvincibleTime)
	{
		m_CurrentInvincibleTime += Time::GetInstance().GetElapsed();
	}
}

void King::Character::Render() const
{
}

void King::Character::Respawn()
{
	GetTransform()->SetPosition(100, 300, 0);
	m_CurrentSpawnTime = 0.f;
}


void King::Character::OnTriggerStay(ColliderComponent* other)
{
	if (m_CurrentInvincibleTime >= m_InvincibleTime)
	{
		Enemy* pEnemy = dynamic_cast<Enemy*>(other->pGameObject);
		if (pEnemy)
		{
			if (!pEnemy->IsBubbled())
			{
				m_CurrentInvincibleTime = 0.f;
				EventSystem::GetInstance().Notify(this, "LIFE_LOST");
			}
		}
	}
}