#include "MiniginPCH.h"
#include "Level1.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TextRenderComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "Character.h"
#include "Box.h"
#include "Zenchan.h"
#include <SDL.h>

Level1::Level1()
	: Scene("Level1")
{
}

void Level1::Initialize()
{
	auto mapGo = new GameObject();
	auto pSprite = new SpriteRenderComponent();
	pSprite->SetSprite("level1.png", 640, 480, 1, 1, 1);
	mapGo->AddComponent(pSprite);
	Add(mapGo);

	auto character = new Character();
	character->SetPosition(100, 400);
	Add(character);

	auto pGo = new Box(40, 1000);
	Add(pGo);

	pGo = new Box(40, 1000);
	pGo->SetPosition(600, 0);
	Add(pGo);

	pGo = new Box(1000, 40);
	Add(pGo);

	pGo = new Box(1000, 25);
	pGo->SetPosition(0, 455);
	Add(pGo);

	pGo = new Box(360, 20);
	pGo->SetPosition(140, 180);
	Add(pGo);

	pGo = new Box(40, 20);
	pGo->SetPosition(40, 180);
	Add(pGo);

	pGo = new Box(40, 20);
	pGo->SetPosition(560, 180);
	Add(pGo);

	pGo = new Box(360, 20);
	pGo->SetPosition(140, 270);
	Add(pGo);


	pGo = new Box(40, 20);
	pGo->SetPosition(40, 270);
	Add(pGo);

	pGo = new Box(40, 20);
	pGo->SetPosition(560, 270);
	Add(pGo);

	pGo = new Box(360, 20);
	pGo->SetPosition(140, 360);
	Add(pGo);

	pGo = new Box(40, 20);
	pGo->SetPosition(40, 360);
	Add(pGo);

	pGo = new Box(40, 20);
	pGo->SetPosition(560, 360);
	Add(pGo);

	Enemy* pEnemy = new Zenchan();
	pEnemy->SetPosition(150, 100);
	Add(pEnemy);

	pEnemy = new Zenchan();
	pEnemy->SetPosition(250, 100);
	Add(pEnemy);

	pEnemy = new Zenchan();
	pEnemy->SetPosition(350, 100);
	Add(pEnemy);

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void Level1::EarlyUpdate()
{
}

void Level1::Update()
{
}
