#pragma once
#include "Scene.h"

namespace King
{
	class TextRenderComponent;
	class ScoreObserver;
	class EnemyObserver;
	class Character;
	class LevelLoader;
	class LifeObserver;
	class Level3 : public Scene
	{
	public:
		Level3();
		~Level3() = default;

		void Initialize() override;
		void EarlyUpdate() override;
		void Update() override;

		void OnActivate() override;

		Level3(const Level3& other) = delete;
		Level3(Level3&& other) = delete;
		Level3& operator=(const Level3& other) = delete;
		Level3& operator=(Level3&& other) = delete;
	private:
		TextRenderComponent* m_ScoreText;
		TextRenderComponent* m_LifeText;

		ScoreObserver* m_pScoreObserver;
		EnemyObserver* m_pEnemyObserver;
		LifeObserver* m_pLifeObserver;

		LevelLoader* m_pLoader;
	};
}