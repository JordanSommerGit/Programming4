#include "Level3.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "TextRenderComponent.h"
#include "PhysicsManager.h"
#include <SDL.h>
#include <string>
#include "LevelLoader.h"

Level3::Level3()
	: Scene("Level3")
{
	LevelLoader* loader = new LevelLoader{ "../Data/Level3.txt" };
	Add(loader);

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void Level3::Initialize()
{
}

void Level3::EarlyUpdate()
{
}

void Level3::Update()
{
}
