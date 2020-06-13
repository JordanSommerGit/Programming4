#pragma once
#include "GameObject.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;
	class Score : public GameObject
	{
	public:
		Score(int value);
		virtual ~Score() = default;

		Score(const Score& other) = delete;
		Score(Score&& other) = delete;
		Score& operator=(const Score& other) = delete;
		Score& operator=(Score&& other) = delete;
		void Initialize() override;
		void Update() override;

	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		int m_Value;

		float m_CurrentLifeTime;
		float m_LifeTime;

		float m_FloatSpeed;
	};
}