#pragma once
#include "GameObject.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;

	class Character : public GameObject
	{
	public:
		Character();
		virtual ~Character() = default;

		Character(const Character& other) = delete;
		Character(Character&& other) = delete;
		Character& operator=(const Character& other) = delete;
		Character& operator=(Character&& other) = delete;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;
		void Render() const override;
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		bool m_ADown;
		bool m_DDown;
		bool m_SpaceDown;
		bool m_JDown;

		bool m_LookingRight;

		float m_CurrentJumpTime;
		float m_JumpTime;

		float m_CurrentAttackAnimTime;
		float m_AttackAnimTime;

		float m_CurrentAttackCDTime;
		float m_AttackCDTime;
	};
}