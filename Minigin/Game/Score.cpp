#include "MiniginPCH.h"
#include "Score.h"
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

King::Score::Score(int value)
	: m_CurrentLifeTime{ 0.f }
	, m_LifeTime{ 2.f }
	, m_FloatSpeed{ 50.f }
	, m_Value{ value }
{
}

void King::Score::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Scores.png", 50, 50, 4, 8, 2);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
	m_pCollider->SetTrigger(true);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	m_pRigidbody->SetApplyGravity(false);
	AddComponent(m_pRigidbody);

	switch (m_Value)
	{
	case 500:
		m_Sprite->SetStartColumn(2);
		break;
	}
}

void King::Score::Update()
{
	m_pRigidbody->SetVelocity(glm::vec3{ 0,-1,0 } * m_FloatSpeed);

	if (m_CurrentLifeTime < m_LifeTime)
	{
		m_CurrentLifeTime += Time::GetInstance().GetElapsed();
	}
	else
	{
		Destroy();
	}
}
