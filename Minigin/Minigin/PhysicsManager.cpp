#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"

void King::PhysicsManager::AddRigidbody(RigidbodyComponent* pRigidbody)
{
	m_pRigidbodies.push_back(pRigidbody);
}

void King::PhysicsManager::RemoveRigidbody(RigidbodyComponent* pRigidbody)
{
	std::vector<RigidbodyComponent*>::iterator it = std::find(m_pRigidbodies.begin(), m_pRigidbodies.end(), pRigidbody);
	if (it != m_pRigidbodies.end())
	{
		m_pRigidbodies.erase(it);
	}
}

bool King::PhysicsManager::CheckCollision(RigidbodyComponent* pToCheck, glm::vec3 targetPosition, glm::vec3& outputVelocity)
{
	bool canMove = false;
	glm::vec3 oldVelocity = outputVelocity;
	for (RigidbodyComponent* pRigidbody : m_pRigidbodies)
	{
		if (pRigidbody == pToCheck)
		{
			continue;
		}
		ColliderComponent* pCollider = pRigidbody->GetCollider();
		pCollider->IsColliding(pToCheck, targetPosition, outputVelocity);
	}
	return canMove;
}

void King::PhysicsManager::EnableDebugRendering(bool enable)
{
	m_DebugRender = enable;
}

bool King::PhysicsManager::IsDebugRendering() const
{
	return m_DebugRender;
}
