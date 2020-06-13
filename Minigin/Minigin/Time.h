#pragma once
#include <chrono>
#include "Singleton.h"

namespace King
{
	class Time : public Singleton<Time>
	{
	public:
		Time();
		void Update();
		float GetElapsed();
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_PrevTime;
		std::chrono::time_point<std::chrono::steady_clock> m_CurrTime;
		float m_DeltaTime;
	};
}

