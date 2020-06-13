#include "MiniginPCH.h"
#include "Transform.h"

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
