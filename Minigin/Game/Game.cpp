#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

Game::Game()
{
	std::shared_ptr<Scene> pScene{ new Level3() };
	SceneManager::GetInstance().AddScene(pScene);
}
