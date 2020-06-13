#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Scene.h"
#include "PhysicsManager.h"

King::ColliderComponent::ColliderComponent(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
{
}

void King::ColliderComponent::Initialize()
{
	m_pTransform = pGameObject->GetTransform();
}

void King::ColliderComponent::Render() const
{
	if (pGameObject->GetScene()->GetPhysicsManager()->IsDebugRendering())
	{
		Renderer::GetInstance().RenderRect(pGameObject->GetTransform()->GetPosition().x, pGameObject->GetTransform()->GetPosition().y, m_Width, m_Height);
	}
}

void King::ColliderComponent::SetRigidbody(RigidbodyComponent* pRigidbody)
{
	m_pRigidbody = pRigidbody;
}

bool King::ColliderComponent::Collide(RigidbodyComponent* pToCheck, glm::vec3 targetPostion, glm::vec3& outputVelocity)
{
	bool isColliding = false;
	std::vector<ColliderComponent*> pColliders = pToCheck->GetColliders();
	for (size_t i = 0; i < pColliders.size(); i++)
	{

		if (targetPostion.x + pColliders[i]->GetWidth() < m_pTransform->GetPosition().x)
		{
			continue;
		}
		if (targetPostion.x > m_pTransform->GetPosition().x + m_Width)
		{
			continue;
		}
		if (targetPostion.y + pColliders[i]->GetHeight() < m_pTransform->GetPosition().y)
		{
			continue;
		}
		if (targetPostion.y > m_pTransform->GetPosition().y + m_Height)
		{
			continue;
		}

		OnTriggerStay(pColliders[i]);

		if (pColliders[i]->IsTrigger())
		{
			continue;
		}

		isColliding = true;

		if (m_pTransform->GetPosition().y > pToCheck->GetTransform()->GetPosition().y + pColliders[i]->GetHeight())
		{
			if (!m_DisableTop)
			{
				switch (m_pRigidbody->GetState())
				{
				case RigidbodyComponent::PhysicState::Static:
					outputVelocity.y = 0;
					break;
				case RigidbodyComponent::PhysicState::Kinematic:
					outputVelocity.y = 0;
					break;
				case RigidbodyComponent::PhysicState::Dynamic:
					outputVelocity.y /= 2;
					m_pRigidbody->SetVelocity(glm::vec3{ m_pRigidbody->GetVelocity().x, outputVelocity.y, 0 });
					break;
				}
			}
		}

		if (m_pTransform->GetPosition().y + m_Height < pToCheck->GetTransform()->GetPosition().y)
		{
			if (!m_DisableBottom)
			{
				switch (m_pRigidbody->GetState())
				{
				case RigidbodyComponent::PhysicState::Static:
					outputVelocity.y = 0;
					break;
				case RigidbodyComponent::PhysicState::Kinematic:
					outputVelocity.y = 0;
					break;
				case RigidbodyComponent::PhysicState::Dynamic:
					outputVelocity.y /= 2;
					m_pRigidbody->SetVelocity(glm::vec3{ m_pRigidbody->GetVelocity().x, outputVelocity.y, 0 });
					break;
				}
			}
		}

		if (m_pTransform->GetPosition().x > pToCheck->GetTransform()->GetPosition().x + pColliders[i]->GetWidth())
		{
			if (!m_DisableLeft)
			{
				switch (m_pRigidbody->GetState())
				{
				case RigidbodyComponent::PhysicState::Static:
					outputVelocity.x = 0;
					break;
				case RigidbodyComponent::PhysicState::Kinematic:
					outputVelocity.x = 0;
					break;
				case RigidbodyComponent::PhysicState::Dynamic:
					outputVelocity.x /= 2;
					m_pRigidbody->SetVelocity(glm::vec3{ outputVelocity.x, m_pRigidbody->GetVelocity().y, 0 });
					break;
				}
			}
		}

		if (m_pTransform->GetPosition().x + m_Width < pToCheck->GetTransform()->GetPosition().x)
		{
			if (!m_DisableRight)
			{
				switch (m_pRigidbody->GetState())
				{
				case RigidbodyComponent::PhysicState::Static:
					outputVelocity.x = 0;
					break;
				case RigidbodyComponent::PhysicState::Kinematic:
					outputVelocity.x = 0;
					break;
				case RigidbodyComponent::PhysicState::Dynamic:
					outputVelocity.x /= 2;
					m_pRigidbody->SetVelocity(glm::vec3{ outputVelocity.x, m_pRigidbody->GetVelocity().y, 0 });
					break;
				}
			}
		}
	}
	return isColliding;
}

void King::ColliderComponent::SetTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

bool King::ColliderComponent::IsTrigger() const
{
	return m_IsTrigger;
}

void King::ColliderComponent::DeactiveBottomCollision(bool deactivate)
{
	m_DisableBottom = deactivate;
}

void King::ColliderComponent::DeactiveTopCollision(bool deactivate)
{
	m_DisableTop = deactivate;
}

void King::ColliderComponent::DeactiveLeftCollision(bool deactivate)
{
	m_DisableLeft = deactivate;
}

void King::ColliderComponent::DeactiveRighCollision(bool deactivate)
{
	m_DisableRight = deactivate;
}

void King::ColliderComponent::OnTriggerEnter(ColliderComponent* other)
{
	pGameObject->OnTriggerEnter(other);
}

void King::ColliderComponent::OnTriggerExit(ColliderComponent* other)
{
	pGameObject->OnTriggerExit(other);
}

void King::ColliderComponent::OnTriggerStay(ColliderComponent* other)
{
	pGameObject->OnTriggerStay(other);
}

float King::ColliderComponent::GetWidth() const
{
	return m_Width;
}

float King::ColliderComponent::GetHeight() const
{
	return m_Height;
}

King::Transform* King::ColliderComponent::GetTransform()
{
	return m_pTransform;
}
