#include "EnemyObserver.h"

King::EnemyObserver::EnemyObserver()
	: m_NewLevel{ false }
	, m_EnemyCount{ 0 }
{
}

void King::EnemyObserver::OnNotify(GameObject*, std::string event)
{
	m_NewLevel = false;
	for (size_t i = 0; i < m_Events->size(); i++)
	{
		if (m_Events[i] == event)
		{
			switch (i)
			{
			case 0:
				m_EnemyCount++;
				break;
			case 1:
				m_EnemyCount--;
				if (m_EnemyCount == 0)
				{
					m_NewLevel = true;
				}
				break;
			}
		}
	}
}

bool King::EnemyObserver::GetNewLevel() const
{
	return m_NewLevel;
}
