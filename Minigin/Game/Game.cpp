#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "EventSystem.h"
#include "EnemyObserver.h"
#include "ScoreObserver.h"
#include "LifeObserver.h"

King::Game::Game()
{

	Scene* pScene = new Level3();
	SceneManager::GetInstance().AddScene(pScene);

	pScene = new Level2();
	SceneManager::GetInstance().AddScene(pScene);

	pScene = new Level1();
	SceneManager::GetInstance().AddScene(pScene);


	if (EventSystem::GetInstance().GetObserver<ScoreObserver>() == nullptr)
	{
		EventSystem::GetInstance().AddObserver(new ScoreObserver());
	}

	if (EventSystem::GetInstance().GetObserver<EnemyObserver>() == nullptr)
	{
		EventSystem::GetInstance().AddObserver(new EnemyObserver());
	}

	if (EventSystem::GetInstance().GetObserver<LifeObserver>() == nullptr)
	{
		EventSystem::GetInstance().AddObserver(new LifeObserver());
	}
}
