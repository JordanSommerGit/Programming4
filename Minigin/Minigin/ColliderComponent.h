#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace King
{
	class Transform;
	class RigidbodyComponent;
	class ColliderComponent : public Component
	{
	public:
		explicit ColliderComponent(float width, float height);
		virtual ~ColliderComponent() = default;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Initialize() override;
		void Render() const override;

		void SetRigidbody(RigidbodyComponent* pRigidbody);

		bool Collide(RigidbodyComponent* pToCheck, glm::vec3 targetPostion, glm::vec3& outputVelocity);
		void SetTrigger(bool isTrigger);
		bool IsTrigger() const;

		void OnTriggerEnter(ColliderComponent* other);
		void OnTriggerExit(ColliderComponent* other);
		void OnTriggerStay(ColliderComponent* other);

		float GetWidth() const;
		float GetHeight() const;

		Transform* GetTransform();
	private:
		RigidbodyComponent* m_pRigidbody;

		Transform* m_pTransform;

		float m_Width;
		float m_Height;

		bool m_IsTrigger;
	};
}