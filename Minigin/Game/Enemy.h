#pragma once
#include "GameObject.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;

	class Enemy : public GameObject
	{
	public:
		Enemy();
		virtual ~Enemy() = default;

		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void OnTriggerStay(ColliderComponent* other);

		void Bubble();
		bool IsBubbled() const;
	protected:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		bool m_IsBubbled;
		float m_CurrentBubbleTime;
		float m_BubbleTime;

		bool m_IsPopping;
		float m_CurrentPopTime;
		float m_PopTime;

		glm::vec3 m_CurrentVelocity;
		float m_Speed;
		float m_FloatSpeed;
	};
}