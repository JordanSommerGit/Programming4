#pragma once
#include "GameObject.h"

namespace King
{
	class Enemy : public GameObject
	{
	public:
		Enemy() = default;
		virtual ~Enemy() = default;

		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void Bubble();
	protected:
		bool m_IsBubbled;
	};
}