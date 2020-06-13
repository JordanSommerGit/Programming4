#include "MiniginPCH.h"
#include "Platform.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

King::Platform::Platform(float width, float height)
	: m_Width(width)
	, m_Height(height)
{
}

void King::Platform::Initialize()
{
	m_pCollider = new ColliderComponent(m_Width, m_Height);
	AddComponent(m_pCollider);
	m_pCollider->DeactiveBottomCollision(true);
	m_pCollider->DeactiveLeftCollision(true);
	m_pCollider->DeactiveRighCollision(true);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Static);
	AddComponent(m_pRigidbody);
}

void King::Platform::EarlyUpdate()
{
}

void King::Platform::Update()
{
}

void King::Platform::Render() const
{

}
