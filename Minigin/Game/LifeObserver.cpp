#include "LifeObserver.h"

King::LifeObserver::LifeObserver()
	: m_IsDead{ false }
	, m_Lives{ 4 }
{
}

void King::LifeObserver::OnNotify(GameObject* pSource, std::string event)
{
	m_IsDead = false;
	for (size_t i = 0; i < m_Events->size(); i++)
	{
		if (m_Events[i] == event)
		{
			switch (i)
			{
			case 0:
				m_Lives--;
				if (m_Lives == 0)
				{
					m_IsDead = true;
					m_Lives = 4;
				}
				break;
			case 1:
				m_Lives++;
				break;
			}
		}
	}
}

bool King::LifeObserver::GetIsDead() const
{
	return m_IsDead;
}

int King::LifeObserver::GetLives() const
{
	return m_Lives;
}
