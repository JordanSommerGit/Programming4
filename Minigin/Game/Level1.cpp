#include "MiniginPCH.h"
#include "Level1.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "TextRenderComponent.h"
#include "LevelLoader.h"
#include <SDL.h>
#include <string>

Level1::Level1()
	: Scene("Level1")
{
}

void Level1::Initialize()
{
	LevelLoader* loader = new LevelLoader{ "../Data/Level1.txt" };
	Add(loader);

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void Level1::EarlyUpdate()
{
}

void Level1::Update()
{
}
