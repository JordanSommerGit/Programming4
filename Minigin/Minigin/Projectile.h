#pragma once
#include "GameObject.h"

namespace King
{
	class SpriteRenderComponent;
	class RigidbodyComponent;
	class ColliderComponent;

	class Projectile : public GameObject
	{
	public:
		Projectile(glm::vec3 direction);
		virtual ~Projectile() = default;

		Projectile(const Projectile& other) = delete;
		Projectile(Projectile&& other) = delete;
		Projectile& operator=(const Projectile& other) = delete;
		Projectile& operator=(Projectile&& other) = delete;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;
		void Render() const override;

		void OnTriggerStay(ColliderComponent* other) override;
	private:
		SpriteRenderComponent* m_Sprite;
		RigidbodyComponent* m_pRigidbody;
		ColliderComponent* m_pCollider;

		glm::vec3 m_Direction;
		float m_Speed;
		float m_FloatSpeed;

		float m_CurrentDeploymentTime;
		float m_DeploymentTime;
		bool m_IsDeployed;

		bool m_IsPopping;
		float m_CurrentPopTime;
		float m_PopTime;
	};
}