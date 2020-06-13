#pragma once
#include "GameObject.h"

namespace King
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Box : public GameObject
	{
	public:
		Box(float width, float height);
		virtual ~Box() = default;

		Box(const Box& other) = delete;
		Box(Box&& other) = delete;
		Box& operator=(const Box& other) = delete;
		Box& operator=(Box&& other) = delete;

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