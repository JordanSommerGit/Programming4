#pragma once
#include "Observer.h"

namespace King
{
	class GameObject;
	class ScoreObserver : public Observer
	{
	public:
		ScoreObserver();
		void OnNotify(GameObject* pSource, std::string event) override;

		int GetScore() const;
	private:
		const std::string m_Events[3] =
		{
			"SCORE_100",
			"SCORE_500",
			"SCORE_1000"
		};

		int m_Score;
	};
}