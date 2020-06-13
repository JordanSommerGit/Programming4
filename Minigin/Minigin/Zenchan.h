#pragma once
#include "Enemy.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;

	class Zenchan : public Enemy
	{
	public:
		Zenchan();
		virtual ~Zenchan() = default;

		Zenchan(const Zenchan& other) = delete;
		Zenchan(Zenchan&& other) = delete;
		Zenchan& operator=(const Zenchan& other) = delete;
		Zenchan& operator=(Zenchan&& other) = delete;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;
		void Render() const override;

		void OnTriggerStay(ColliderComponent* other) override;
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		glm::vec3 m_CurrentVelocity;
		float m_Speed;
		float m_FloatSpeed;

		bool m_IsPopping;
		float m_CurrentPopTime;
		float m_PopTime;
	};
}