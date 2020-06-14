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

		void Respawn();

		void OnTriggerStay(ColliderComponent* other) override;
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		bool m_ADown;
		bool m_DDown;
		bool m_WDown;
		bool m_FDown;

		bool m_LookingRight;

		float m_CurrentSpawnTime;
		float m_SpawnTime;

		float m_CurrentJumpTime;
		float m_JumpTime;

		float m_CurrentAttackAnimTime;
		float m_AttackAnimTime;

		float m_CurrentAttackCDTime;
		float m_AttackCDTime;

		float m_CurrentInvincibleTime;
		float m_InvincibleTime;
	};
}