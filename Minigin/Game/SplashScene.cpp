#include "MiniginPCH.h"
#include "SplashScene.h"
#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <SDL.h>

King::SplashScene::SplashScene()
	: Scene("Splash")
{
}

void King::SplashScene::Initialize()
{
	auto mapGo = new GameObject();
	auto pSprite = new SpriteRenderComponent();
	pSprite->SetSprite("Title.png", 512, 424, 1, 1, 1);
	mapGo->AddComponent(pSprite);
	Add(mapGo);
}

void King::SplashScene::Update()
{
	if (InputManager::GetInstance().GetEvent().type == SDL_EventType::SDL_KEYDOWN)
	{
		if (InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			SceneManager::GetInstance().SetActiveScene("Level1");
		}
	}
}
