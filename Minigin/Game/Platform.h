#pragma once
#include "GameObject.h"

namespace King
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Platform : public GameObject
	{
	public:
		Platform(float width, float height);
		virtual ~Platform() = default;

		Platform(const Platform& other) = delete;
		Platform(Platform&& other) = delete;
		Platform& operator=(const Platform& other) = delete;
		Platform& operator=(Platform&& other) = delete;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;
		void Render() const override;
	private:
		ColliderComponent* m_pCollider;
		RigidbodyComponent* m_pRigidbody;

		float m_Width;
		float m_Height;
	};
}