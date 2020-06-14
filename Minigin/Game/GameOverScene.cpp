#include "GameOverScene.h"
#include "GameObject.h"
#include "SpriteRenderComponent.h"

King::GameOverScene::GameOverScene()
	: Scene("GameOver")
{
}

void King::GameOverScene::Initialize()
{
	auto mapGo = new GameObject();
	auto pSprite = new SpriteRenderComponent();
	pSprite->SetSprite("GameOver.png", 512, 424, 1, 1, 1);
	mapGo->AddComponent(pSprite);
	Add(mapGo);
}