#pragma once
#include "Scene.h"

namespace King
{
	class SplashScene : public Scene
	{
	public:
		SplashScene();
		~SplashScene() = default;

		void Initialize() override;
		void Update() override;

		SplashScene(const SplashScene& other) = delete;
		SplashScene(SplashScene&& other) = delete;
		SplashScene& operator=(const SplashScene& other) = delete;
		SplashScene& operator=(SplashScene&& other) = delete;
	};
}