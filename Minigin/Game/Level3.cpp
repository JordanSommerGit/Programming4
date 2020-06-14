#include "Level3.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "LevelLoader.h"
#include "ScoreObserver.h"
#include "EnemyObserver.h"
#include "LifeObserver.h"
#include "EventSystem.h"
#include "Font.h"
#include "Character.h"

King::Level3::Level3()
	: Scene("Level3")
{
}

void King::Level3::Initialize()
{
	m_pLoader = new LevelLoader{ "../Data/Level3.txt" };
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

void King::Level3::EarlyUpdate()
{
}

void King::Level3::Update()
{
	m_ScoreText->SetText(std::to_string(m_pScoreObserver->GetScore()));
	m_LifeText->SetText(std::to_string(m_pLifeObserver->GetLives()));

	if (m_pLoader->GetCharacter()->GetTransform()->GetPosition().y > 424.f)
	{
		m_pLoader->GetCharacter()->GetTransform()->SetPosition(m_pLoader->GetCharacter()->GetTransform()->GetPosition().x, -39, 0);
	}
}
