#pragma once
#include "GameObject.h"

namespace King
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Bounds : public GameObject
	{
	public:
		Bounds(float width, float height);
		virtual ~Bounds() = default;

		Bounds(const Bounds& other) = delete;
		Bounds(Bounds&& other) = delete;
		Bounds& operator=(const Bounds& other) = delete;
		Bounds& operator=(Bounds&& other) = delete;

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