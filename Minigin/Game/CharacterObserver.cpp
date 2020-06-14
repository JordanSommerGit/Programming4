#include "CharacterObserver.h"

King::CharacterObserver::CharacterObserver()
	: m_IsDead{ false }
	, m_Lives{ 4 }
	, m_Player2Spawned{ false }
{
}

void King::CharacterObserver::OnNotify(GameObject* pSource, std::string event)
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
			case 2:
				m_Player2Spawned = true;
				break;
			}
		}
	}
}

bool King::CharacterObserver::GetIsDead() const
{
	return m_IsDead;
}

int King::CharacterObserver::GetLives() const
{
	return m_Lives;
}

bool King::CharacterObserver::GetPlayer2Spawned() const
{
	return m_Player2Spawned;
}
