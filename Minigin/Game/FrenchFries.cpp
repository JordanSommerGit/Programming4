#include "MiniginPCH.h"
#include "FrenchFries.h"
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
#include "Scene.h"
#include "Score.h"

void King::FrenchFries::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("PickUps.png", 50, 50, 1, 2, 1);
	m_Sprite->SetStartColumn(1);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
	m_pCollider->SetTrigger(true);
	AddComponent(m_pCollider);

	GameObject* pSubCollider = new GameObject();
	m_pCollider = new ColliderComponent(46, 46);
	pSubCollider->AddComponent(m_pCollider);
	AddChild(pSubCollider);
	pSubCollider->GetTransform()->SetPosition(2, 2, 0);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	AddComponent(m_pRigidbody);
}

void King::FrenchFries::Update()
{
	if (m_pRigidbody->GetVelocity().y == 0)
	{
		m_IsCollectable = true;
	}
}

void King::FrenchFries::OnCollect()
{
	Score* pScore = new Score(500);
	GetScene()->Add(pScore);
	pScore->GetTransform()->SetPosition(GetTransform()->GetPosition());
}
