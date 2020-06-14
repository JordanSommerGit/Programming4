#include "Level2.h"
#include "GameObject.h"
#include "Transform.h"
#include "Character.h"
#include "TextRenderComponent.h"
#include "LevelLoader.h"
#include "ScoreObserver.h"
#include "EnemyObserver.h"
#include "LifeObserver.h"
#include "EventSystem.h"
#include "Font.h"
#include "Time.h"

King::Level2::Level2()
	: Scene("Level2")
	, m_CurrentNextLevelTime{ 0.f }
	, m_NextLevelTime{ 3.f }
	, m_NextLevel{ false }
{
}

void King::Level2::Initialize()
{
	m_pLoader = new LevelLoader{ "../Data/Level2.txt" };
	Add(m_pLoader);

	auto pText = new GameObject();
	m_ScoreText = new TextRenderComponent();
	pText->AddComponent(m_ScoreText);
	Add(pText);
	std::shared_ptr<Font> pFont{ new Font("../Data/Lingua.otf", 36) };
	m_ScoreText->SetFont(pFont);
	pText->GetTransform()->SetPosition(0, 424, 0);

	pText = new GameObject();
	m_LifeText = new TextRenderComponent();
	pText->AddComponent(m_LifeText);
	Add(pText);
	m_LifeText->SetFont(pFont);
	pText->GetTransform()->SetPosition(496, 424, 0);

	m_pScoreObserver = EventSystem::GetInstance().GetObserver<ScoreObserver>();
	m_pEnemyObserver = EventSystem::GetInstance().GetObserver<EnemyObserver>();
	m_pLifeObserver = EventSystem::GetInstance().GetObserver<LifeObserver>();

	//GetPhysicsManager()->EnableDebugRendering(true);
}

void King::Level2::EarlyUpdate()
{
}

void King::Level2::Update()
{
	m_ScoreText->SetText(std::to_string(m_pScoreObserver->GetScore()));
	m_LifeText->SetText(std::to_string(m_pLifeObserver->GetLives()));

	if (m_pEnemyObserver->GetNewLevel())
	{
		m_NextLevel = true;
	}

	if (m_pLifeObserver->GetIsDead())
	{
		SceneManager::GetInstance().SetActiveScene("Splash");
	}

	if (m_NextLevel)
	{
		m_CurrentNextLevelTime += Time::GetInstance().GetElapsed();
	}

	if (m_CurrentNextLevelTime >= m_NextLevelTime)
	{
		SceneManager::GetInstance().SetActiveScene("Level3");
	}
}

void King::Level2::OnActivate()
{

}
