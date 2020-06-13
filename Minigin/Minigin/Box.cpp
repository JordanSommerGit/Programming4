#include "MiniginPCH.h"
#include "Box.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

King::Box::Box(float width, float height)
	: m_Width( width )
	, m_Height( height )
{
}

void King::Box::Initialize()
{
	m_pCollider = new ColliderComponent(m_Width, m_Height);
	AddComponent(m_pCollider);

	m_pRigidbody = new RigidbodyComponent(RigidbodyComponent::PhysicState::Static);
	AddComponent(m_pRigidbody);
}

void King::Box::EarlyUpdate()
{
}

void King::Box::Update()
{
}

void King::Box::Render() const
{
	
}
