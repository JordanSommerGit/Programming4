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
	for (auto& scene : m_Scenes)
	{
		scene->EarlyUpdate();
	}

	for (auto& scene : m_Scenes)
	{
		scene->RootEarlyUpdate();
	}
}

void King::SceneManager::Update()
{
	for (auto& scene : m_Scenes)
	{
		scene->RootInitialize();
	}

	for (auto& scene : m_Scenes)
	{
		scene->Update();
	}

	for (auto& scene : m_Scenes)
	{
		scene->RootUpdate();
	}
}

void King::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}

	for (const auto& scene : m_Scenes)
	{
		scene->RootRender();
	}
}

King::Scene& King::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void King::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
}
