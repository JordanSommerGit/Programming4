#include "ScoreObserver.h"

King::ScoreObserver::ScoreObserver()
	: m_Score{ 0 }
{
}

void King::ScoreObserver::OnNotify(GameObject* pSource, std::string event)
{
	for (size_t i = 0; i < m_Events->size(); i++)
	{
		if (m_Events[i] == event)
		{
			switch (i)
			{
			case 0:
				m_Score += 100;
				break;
			case 1:
				m_Score += 500;
				break;
			case 2:
				m_Score += 1000;
				break;
			}
		}
	}
}

int King::ScoreObserver::GetScore() const
{
	return m_Score;
}
