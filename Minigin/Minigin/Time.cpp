#include "MiniginPCH.h"
#include "Time.h"

King::Time::Time()
	: m_DeltaTime{ 0.0f }
{
	m_PrevTime = std::chrono::high_resolution_clock::now();
}

void King::Time::Update()
{
	m_CurrTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(m_CurrTime - m_PrevTime).count();
	m_PrevTime = m_CurrTime;
}

float King::Time::GetElapsed()
{
	return m_DeltaTime;
}