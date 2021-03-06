#include "MiniginPCH.h"
#include "Level1.h"
#include "GameObject.h"
#include "Transform.h"
#include "Character.h"
#include "TextRenderComponent.h"
#include "LevelLoader.h"
#include "ScoreObserver.h"
#include "EnemyObserver.h"
#include "CharacterObserver.h"
#include "EventSystem.h"
#include "Font.h"
#include "Time.h"
#include "InputManager.h"

King::Level1::Level1()
	: Scene("Level1")
	, m_CurrentNextLevelTime{ 0.f }
	, m_NextLevelTime{ 3.f }
	, m_NextLevel{ false }
{
}

void King::Level1::Initialize()
{
	m_pLoader = new LevelLoader{ "../Data/Level1.txt" };
	Add(m_pLoader);

	auto pText = new GameObject();
	m_ScoreText = new TextRenderComponent();
	pText->AddComponent(m_ScoreText);
	Add(pText);
	std::shared_ptr<Font> pFont{ new Font("../Data/Lingua.otf", 36) };
	m_ScoreText->SetFont(pFont);
	pText->GetTransform()->SetPosition(0, 424,0);

	pText = new GameObject();
	m_LifeText = new TextRenderComponent();
	pText->AddComponent(m_LifeText);
	Add(pText);
	m_LifeText->SetFont(pFont);
	pText->GetTransform()->SetPosition(496, 424, 0);

	m_pScoreObserver = EventSystem::GetInstance().GetObserver<ScoreObserver>();
	m_pEnemyObserver = EventSystem::GetInstance().GetObserver<EnemyObserver>();
	m_pCharacterObserver = EventSystem::GetInstance().GetObserver<CharacterObserver>();

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void King::Level1::EarlyUpdate()
{
}

void King::Level1::Update()
{
	m_ScoreText->SetText(std::to_string(m_pScoreObserver->GetScore()));
	m_LifeText->SetText(std::to_string(m_pCharacterObserver->GetLives()));

	if (!m_Player2Spawned)
	{
		if (InputManager::GetInstance().GetEvent().type == SDL_KEYDOWN && InputManager::GetInstance().GetEvent().key.keysym.scancode == SDL_SCANCODE_P)
		{
			m_pLoader->SpawnBob();
			EventSystem::GetInstance().Notify(nullptr, "PLAYER2_SPAWNED");
			m_Player2Spawned = true;
		}
		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY, 1))
		{
			m_pLoader->SpawnBob();
			EventSystem::GetInstance().Notify(nullptr, "PLAYER2_SPAWNED");
			m_Player2Spawned = true;
		}
	}

	if (m_pCharacterObserver->GetIsDead())
	{
		m_pLoader->GetBub()->Destroy();
		SceneManager::GetInstance().SetActiveScene("GameOver");
	}

	if (m_pEnemyObserver->GetNewLevel())
	{
		m_NextLevel = true;
	}

	if (m_NextLevel)
	{
		m_CurrentNextLevelTime += Time::GetInstance().GetElapsed();
	}
	
	if (m_CurrentNextLevelTime >= m_NextLevelTime)
	{
		SceneManager::GetInstance().SetActiveScene("Level2");
	}
}

void King::Level1::OnActivate()
{

}
