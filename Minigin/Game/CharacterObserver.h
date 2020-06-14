#pragma once
#include "Observer.h"

namespace King
{
	class GameObject;
	class CharacterObserver : public Observer
	{
	public:
		CharacterObserver();
		void OnNotify(GameObject* pSource, std::string event) override;

		bool GetIsDead() const;
		int GetLives() const;
		bool GetPlayer2Spawned() const;
	private:
		const std::string m_Events[3] =
		{
			"LIFE_LOST",
			"LIFE_GAINED",
			"PLAYER2_SPAWNED"
		};

		int m_Lives;
		bool m_IsDead;
		bool m_Player2Spawned;
	};
}