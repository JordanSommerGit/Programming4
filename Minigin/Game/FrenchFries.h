#pragma once
#include "PickUp.h"

namespace King
{
	class FrenchFries : public PickUp
	{
	public:
		FrenchFries() = default;
		virtual ~FrenchFries() = default;

		FrenchFries(const FrenchFries& other) = delete;
		FrenchFries(FrenchFries&& other) = delete;
		FrenchFries& operator=(const FrenchFries& other) = delete;
		FrenchFries& operator=(FrenchFries&& other) = delete;

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