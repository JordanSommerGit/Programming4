#include "MiniginPCH.h"
#include "Bob.h"
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

King::Bob::Bob()
{
	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_UP, new JumpCommand(this));
	InputManager::GetInstance().AddKeyboardCommand(SDL_SCANCODE_L, new ShootCommand(this));
	InputManager::GetInstance().AddControllerCommand(1, ControllerButton::ButtonA, new JumpCommand(this));
	InputManager::GetInstance().AddControllerCommand(1, ControllerButton::ButtonX, new ShootCommand(this));
}

void King::Bob::Initialize()
{

	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Character.png", 40, 40, 12, 8, 8, 6);
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

void King::Bob::Update()
{
	if (m_CurrentSpawnTime < m_SpawnTime)
	{
		m_CurrentSpawnTime += Time::GetInstance().GetElapsed();
		return;
	}

	//Input
	if (InputManager::GetInstance().GetEvent().type == SDL_EventType::SDL_KEYDOWN)
	{
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			m_RightDown = true;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			m_LeftDown = true;
		}
	}

	if (InputManager::GetInstance().GetEvent().type == SDL_EventType::SDL_KEYUP)
	{
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			m_RightDown = false;
		}
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			m_LeftDown = false;
		}
	}

	//Animation
	if (m_LookingRight)
	{
		if (m_CurrentAttackAnimTime < m_AttackAnimTime)
		{
			m_Sprite->SetStartRow(8);
		}
		else
		{
			m_Sprite->SetStartRow(6);
		}
	}
	else
	{
		if (m_CurrentAttackAnimTime < m_AttackAnimTime)
		{
			m_Sprite->SetStartRow(10);
		}
		else
		{
			m_Sprite->SetStartRow(7);
		}
	}

	//Movement
	float x = InputManager::GetInstance().GetLeftstick(1).x;
	if (x > 0.1f)
	{
		m_LookingRight = true;
	}
	if (x < -0.1f)
	{
		m_LookingRight = false;
	}
	m_pRigidbody->SetVelocity(glm::vec3{ x * 150,m_pRigidbody->GetVelocity().y,0 });
	if (m_RightDown)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ 150,m_pRigidbody->GetVelocity().y,0 });
		m_LookingRight = true;
	}
	if (m_LeftDown)
	{
		m_pRigidbody->SetVelocity(glm::vec3{ -150,m_pRigidbody->GetVelocity().y,0 });
		m_LookingRight = false;
	}
}

void King::Bob::Jump()
{
	if (m_pRigidbody->IsColliding() && m_CurrentJumpTime >= m_JumpTime)
	{
		m_CurrentJumpTime = 0.f;
	}
}

void King::Bob::Shoot()
{
	if (m_CurrentAttackCDTime >= m_AttackCDTime)
	{
		Projectile* pProjectile;
		if (m_LookingRight)
		{
			pProjectile = new Projectile(glm::vec3{ 1,0,0 }, Projectile::Color::Blue);
		}
		else
		{
			pProjectile = new Projectile(glm::vec3{ -1,0,0 }, Projectile::Color::Blue);
		}
		GetScene()->Add(pProjectile);
		pProjectile->GetTransform()->SetPosition(this->GetTransform()->GetPosition());

		m_CurrentAttackCDTime = 0.f;
		m_CurrentAttackAnimTime = 0.f;
	}
}
