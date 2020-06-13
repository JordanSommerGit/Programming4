#include "Level2.h"
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
#include "Bounds.h"
#include "Platform.h"
#include "Zenchan.h"
#include <SDL.h>
#include <string>
#include "LevelLoader.h"

Level2::Level2()
	: Scene("Level2")
{
}

void Level2::Initialize()
{
	LevelLoader* loader = new LevelLoader{ "../Data/Level2.txt" };
	Add(loader);

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void Level2::EarlyUpdate()
{
}

void Level2::Update()
{
}
