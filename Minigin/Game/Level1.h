#pragma once
#include "Scene.h"

namespace King
{
	class TextRenderComponent;
	class ScoreObserver;
	class EnemyObserver;
	class LifeObserver;
	class Level1 : public Scene
	{
	public:
		Level1();
		~Level1() = default;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;

		Level1(const Level1& other) = delete;
		Level1(Level1&& other) = delete;
		Level1& operator=(const Level1& other) = delete;
		Level1& operator=(Level1&& other) = delete;
	private:
		TextRenderComponent* m_ScoreText;
		TextRenderComponent* m_LifeText;

		ScoreObserver* m_pScoreObserver;
		EnemyObserver* m_pEnemyObserver;
		LifeObserver* m_pLifeObserver;

		float m_CurrentNextLevelTime;
		float m_NextLevelTime;
		bool m_NextLevel;
	};
}