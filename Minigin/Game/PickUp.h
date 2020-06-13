#pragma once
#include "GameObject.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;
	class PickUp : public GameObject
	{
	public:
		PickUp() = default;
		virtual ~PickUp() = default;

		PickUp(const PickUp& other) = delete;
		PickUp(PickUp&& other) = delete;
		PickUp& operator=(const PickUp& other) = delete;
		PickUp& operator=(PickUp&& other) = delete;

		void OnTriggerStay(ColliderComponent * other) override;

		void Collect();
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;
	protected:
		virtual void OnCollect();

		bool m_IsCollectable;
	};
}