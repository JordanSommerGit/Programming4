#pragma once
#include <vector>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace King
{
	class RigidbodyComponent;

	class PhysicsManager
	{
	public:
		void AddRigidbody(RigidbodyComponent* pRigidbody);
		void RemoveRigidbody(RigidbodyComponent* pRigidbody);

		bool CheckCollision(RigidbodyComponent* pToCheck, glm::vec3 targetPosition, glm::vec3& outputVelocity);
		void EnableDebugRendering(bool enable);
		bool IsDebugRendering() const;
	private:
		std::vector<RigidbodyComponent*> m_pRigidbodies;
		bool m_DebugRender;
	};
}