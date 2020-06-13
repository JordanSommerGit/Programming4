#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "Time.h"
#include "Scene.h"
#include "PhysicsManager.h"

King::RigidbodyComponent::RigidbodyComponent(PhysicState physicState)
	: m_PhysicsState{ physicState }
	, m_Drag( 2.f )
	, m_Gravity( 60.f )
{
}

void King::RigidbodyComponent::Initialize()
{
	m_pColliderComponent = pGameObject->GetComponent<ColliderComponent>();
	m_pColliderComponent->SetRigidbody(this);
	m_pTransform = pGameObject->GetTransform();
	pGameObject->GetScene()->GetPhysicsManager()->AddRigidbody(this);
}

void King::RigidbodyComponent::Update()
{
	if (m_PhysicsState == PhysicState::Static)
	{
		return;
	}

	if (m_PhysicsState != PhysicState::Kinematic)
	{
		m_Velocity += glm::vec3{ 0,1,0 } *m_Gravity;
	}
	
	glm::vec3 targetPosition = m_pTransform->GetPosition() + m_Velocity * Time::GetInstance().GetElapsed();
	if (!m_pColliderComponent->IsTrigger())
	{
		pGameObject->GetScene()->GetPhysicsManager()->CheckCollision(this, targetPosition, m_Velocity);
	}
	targetPosition = m_pTransform->GetPosition() + m_Velocity * Time::GetInstance().GetElapsed();
	m_pTransform->SetPosition(targetPosition);

	m_Velocity /= m_Drag;
}

King::ColliderComponent* King::RigidbodyComponent::GetCollider()
{
	return m_pColliderComponent;
}

King::Transform* King::RigidbodyComponent::GetTransform()
{
	return m_pTransform;
}

glm::vec3 King::RigidbodyComponent::GetVelocity() const
{
	return m_Velocity;
}

void King::RigidbodyComponent::SetVelocity(glm::vec3 velocity)
{
	m_Velocity = velocity;
}

King::RigidbodyComponent::PhysicState King::RigidbodyComponent::GetState() const
{
	return m_PhysicsState;
}

void King::RigidbodyComponent::AddForce(glm::vec3 force)
{
	m_Velocity += force;
}

King::RigidbodyComponent::PhysicState King::RigidbodyComponent::GetState()
{
	return m_PhysicsState;
}
