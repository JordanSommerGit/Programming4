#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void King::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void King::SceneManager::EarlyUpdate()
{
	m_pActiveScene->EarlyUpdate();
	m_pActiveScene->RootEarlyUpdate();
}

void King::SceneManager::Update()
{
	m_pActiveScene->RootInitialize();
	m_pActiveScene->Update();
	m_pActiveScene->RootUpdate();
}

void King::SceneManager::Render()
{
	m_pActiveScene->Render();
	m_pActiveScene->RootRender();
}

King::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		delete pScene;
		pScene = nullptr;
	}
}

King::Scene& King::SceneManager::CreateScene(const std::string& name)
{
	auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	m_pActiveScene = scene;
	return *scene;
}

void King::SceneManager::AddScene(Scene* pScene)
{
	m_Scenes.push_back(pScene);
	m_pActiveScene = pScene;
}

void King::SceneManager::SetActiveScene(const std::string& name)
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->GetName() == name)
		{
			m_pActiveScene = m_Scenes[i];
			if (m_pActiveScene->IsInitialized())
			{
				m_pActiveScene->OnActivate();
			}
		}
	}
}
