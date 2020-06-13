#include "MiniginPCH.h"
#include "PickUp.h"
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

void King::PickUp::Initialize()
{
	m_Sprite = new SpriteRenderComponent();
	m_Sprite->SetSprite("Projectile.png", 50, 50, 12, 8, 8, 0);
	AddComponent(m_Sprite);

	m_pCollider = new ColliderComponent(50, 50);
	m_pCollider->SetTrigger(true);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Dynamic);
	m_pRigidbody->SetApplyGravity(false);
	AddComponent(m_pRigidbody);
}

void King::PickUp::EarlyUpdate()
{
}

void King::PickUp::Update()
{
}

void King::PickUp::Render() const
{
}

void King::PickUp::OnTriggerStay(ColliderComponent* other)
{
}
