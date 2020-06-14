#pragma once
#include "Scene.h"

namespace King
{
	class TextRenderComponent;
	class ScoreObserver;
	class EnemyObserver;
	class CharacterObserver;
	class LevelLoader;
	class Level2 : public Scene
	{
	public:
		Level2();
		~Level2() = default;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;

		void OnActivate() override;

		Level2(const Level2& other) = delete;
		Level2(Level2&& other) = delete;
		Level2& operator=(const Level2& other) = delete;
		Level2& operator=(Level2&& other) = delete;
	private:
		TextRenderComponent* m_ScoreText;
		TextRenderComponent* m_LifeText;

		ScoreObserver* m_pScoreObserver;
		EnemyObserver* m_pEnemyObserver;
		CharacterObserver* m_pCharacterObserver;

		LevelLoader* m_pLoader;

		float m_CurrentNextLevelTime;
		float m_NextLevelTime;
		bool m_NextLevel;

		bool m_Player2Spawned;
	};
}