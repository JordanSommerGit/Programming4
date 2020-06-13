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

King::Character::Character()
	: m_Sprite{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_CurrentJumpTime{ 0.4f }
	, m_JumpTime{ 0.4f }
	, m_CurrentAttackAnimTime{ 0.3f }
	, m_AttackAnimTime{ 0.3f }
	, m_CurrentAttackCDTime{ 0.5f }
	, m_AttackCDTime{ 0.5f }
{
}

void King::Character::Initialize()
{
	using namespace King;

	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Character.png", 50, 50, 12, 8, 8, 0);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
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
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			m_SpaceDown = true;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_J)
		{
			m_JDown = true;
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
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			m_SpaceDown = false;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_J)
		{
			m_JDown = false;
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
	if (m_SpaceDown)
	{
		if (m_pRigidbody->GetVelocity().y == 0)
		{
			m_CurrentJumpTime = 0.f;
		}
	}
	if (m_JDown && m_CurrentAttackCDTime >= m_AttackCDTime)
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
}

void King::Character::Render() const
{
}
