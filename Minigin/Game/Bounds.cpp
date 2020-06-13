#include "MiniginPCH.h"
#include "Bounds.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

King::Bounds::Bounds(float width, float height)
	: m_Width( width )
	, m_Height( height )
{
}

void King::Bounds::Initialize()
{
	m_pCollider = new ColliderComponent(m_Width, m_Height);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Static);
	AddComponent(m_pRigidbody);
}

void King::Bounds::EarlyUpdate()
{
}

void King::Bounds::Update()
{
}

void King::Bounds::Render() const
{
	
}
