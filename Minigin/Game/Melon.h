#pragma once
#include "PickUp.h"

namespace King
{
	class Melon : public PickUp
	{
	public:
		Melon() = default;
		virtual ~Melon() = default;

		Melon(const Melon& other) = delete;
		Melon(Melon&& other) = delete;
		Melon& operator=(const Melon& other) = delete;
		Melon& operator=(Melon&& other) = delete;

		void Initialize() override;
		void Update() override;

	protected:
		void OnCollect() override;
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;
	};
}