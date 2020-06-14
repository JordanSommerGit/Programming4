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

void King::Character::EarlyUpdate()
{
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