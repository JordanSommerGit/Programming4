#pragma once
#include "Observer.h"

namespace King
{
	class GameObject;
	class LifeObserver : public Observer
	{
	public:
		LifeObserver();
		void OnNotify(GameObject* pSource, std::string event) override;

		bool GetIsDead() const;
		int GetLives() const;
	private:
		const std::string m_Events[2] =
		{
			"LIFE_LOST",
			"LIFE_GAINED"
		};

		int m_Lives;
		bool m_IsDead;
	};
}