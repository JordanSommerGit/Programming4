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
	m_pColliderComponents = pGameObject->GetComponents<ColliderComponent>(true);
	for (ColliderComponent* col : m_pColliderComponents)
	{
		col->SetRigidbody(this);
	}
	m_pTransform = pGameObject->GetTransform();
	pGameObject->GetScene()->GetPhysicsManager()->AddRigidbody(this);
}

void King::RigidbodyComponent::Update()
{
	if (m_PhysicsState == PhysicState::Static)
	{
		return;
	}

	if (m_ApplyGravity)
	{
		m_Velocity += glm::vec3{ 0,1,0 } * m_Gravity;
	}
	
	glm::vec3 targetPosition = m_pTransform->GetPosition() + m_Velocity * Time::GetInstance().GetElapsed();

	m_IsColliding = false;
	m_IsColliding = pGameObject->GetScene()->GetPhysicsManager()->CheckCollision(this, targetPosition, m_Velocity);

	targetPosition = m_pTransform->GetPosition() + m_Velocity * Time::GetInstance().GetElapsed();
	m_pTransform->SetPosition(targetPosition);

	if (m_ApplyDrag)
	{
		m_Velocity /= m_Drag;
	}
}

King::ColliderComponent* King::RigidbodyComponent::GetCollider()
{
	return m_pColliderComponents[0];
}

std::vector<King::ColliderComponent*> King::RigidbodyComponent::GetColliders()
{
	return m_pColliderComponents;
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

bool King::RigidbodyComponent::IsColliding() const
{
	return m_IsColliding;
}

void King::RigidbodyComponent::SetApplyGravity(bool apply)
{
	m_ApplyGravity = apply;
}

void King::RigidbodyComponent::SetApplyDrag(bool apply)
{
	m_ApplyDrag = apply;
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
