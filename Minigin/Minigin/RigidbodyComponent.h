#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include <vector>

namespace King
{
	class ColliderComponent;
	class Transform;

	class RigidbodyComponent : public Component
	{
	public:
		enum PhysicState
		{
			Dynamic,
			Kinematic,
			Static
		};

		explicit RigidbodyComponent(PhysicState physicsState);
		virtual ~RigidbodyComponent() = default;

		RigidbodyComponent(const RigidbodyComponent& other) = delete;
		RigidbodyComponent(RigidbodyComponent&& other) = delete;
		RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
		RigidbodyComponent& operator=(RigidbodyComponent&& other) = delete;

		void Initialize() override;
		void Update() override;

		ColliderComponent* GetCollider();
		std::vector<ColliderComponent*> GetColliders();
		Transform* GetTransform();

		glm::vec3 GetVelocity() const;
		void SetVelocity(glm::vec3 velocity);

		void SetApplyGravity(bool apply);

		PhysicState GetState() const;

		void AddForce(glm::vec3 force);

		PhysicState GetState();
	private:
		PhysicState m_PhysicsState;

		std::vector<ColliderComponent*> m_pColliderComponents;
		Transform* m_pTransform;

		glm::vec3 m_Velocity;
		float m_Drag;
		bool m_ApplyGravity = true;
		float m_Gravity;
	};
}