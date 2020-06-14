#pragma once
#include "Observer.h"

namespace King
{
	class GameObject;
	class EnemyObserver : public Observer
	{
	public:
		EnemyObserver();
		void OnNotify(GameObject* pSource, std::string event) override;

		bool GetNewLevel() const;
	private:
		const std::string m_Events[2] =
		{
			"ENEMY_SPAWNED",
			"ENEMY_KILLED"
		};

		int m_EnemyCount;
		bool m_NewLevel;
	};
}