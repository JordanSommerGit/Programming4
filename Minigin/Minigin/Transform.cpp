#include "MiniginPCH.h"
#include "Transform.h"
#include "GameObject.h"

void King::Transform::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}

const glm::vec3 King::Transform::GetPosition() const
{
	if (m_pGameObject->GetParent() != nullptr)
	{
		glm::vec3 parentPosition = m_pGameObject->GetParent()->GetTransform()->GetPosition();
		return  parentPosition  + m_Position;
	}
	return m_Position;
}

void King::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void King::Transform::SetPosition(glm::vec3 position)
{
	m_Position = position;
}
