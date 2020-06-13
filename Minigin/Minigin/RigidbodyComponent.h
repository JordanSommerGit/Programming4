#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

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
		Transform* GetTransform();

		glm::vec3 GetVelocity() const;
		void SetVelocity(glm::vec3 velocity);

		PhysicState GetState() const;

		void AddForce(glm::vec3 force);

		PhysicState GetState();
	private:
		PhysicState m_PhysicsState;

		ColliderComponent* m_pColliderComponent;
		Transform* m_pTransform;

		glm::vec3 m_Velocity;
		float m_Drag;
		float m_Gravity;
	};
}