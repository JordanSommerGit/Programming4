#pragma once
#include "Scene.h"

namespace King
{
	class GameOverScene : public Scene
	{
	public:
		GameOverScene();
		~GameOverScene() = default;

		void Initialize() override;

		GameOverScene(const GameOverScene& other) = delete;
		GameOverScene(GameOverScene&& other) = delete;
		GameOverScene& operator=(const GameOverScene& other) = delete;
		GameOverScene& operator=(GameOverScene&& other) = delete;
	};
}