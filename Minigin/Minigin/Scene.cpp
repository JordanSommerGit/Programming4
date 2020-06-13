#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidbodyComponent.h"

using namespace King;

unsigned int Scene::m_IdCounter = 0;

PhysicsManager* King::Scene::GetPhysicsManager()
{
	return m_pPhysicsManager;
}

Scene::Scene(const std::string& name)
	: m_Name(name)
{
	m_pPhysicsManager = new PhysicsManager();
}

Scene::~Scene()
{
	for (SceneObject* object : m_Objects)
	{
		if (object)
		{
			delete object;
			object = nullptr;
		}
	}
	delete m_pPhysicsManager;
}

void Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
	object->SetScene(this);
}

void King::Scene::Initialize()
{

}

void King::Scene::EarlyUpdate()
{
}

void Scene::Update()
{
}

void Scene::Render() const
{
}

void King::Scene::RootInitialize()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->IsInitialized())
		{
			continue;
		}
		m_Objects[i]->Initialize();
		m_Objects[i]->RootInitialize();
	}
}

void King::Scene::RootEarlyUpdate()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (!m_Objects[i]->IsInitialized())
		{
			continue;
		}
		m_Objects[i]->EarlyUpdate();
		m_Objects[i]->RootEarlyUpdate();
	}
}

void King::Scene::RootUpdate()
{
	for (size_t i=0; i < m_Objects.size(); i++)
	{
		if (!m_Objects[i]->IsInitialized())
		{
			continue;
		}
		m_Objects[i]->Update();
		m_Objects[i]->RootUpdate();
	}

	CleanUp();
}

void King::Scene::RootRender()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Render();
		m_Objects[i]->RootRender();
	}
}

void King::Scene::CleanUp()
{
	std::vector<SceneObject*> toDestroy;
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->IsDestroyed())
		{
			toDestroy.push_back(m_Objects[i]);
		}
	}

	for (size_t i = 0; i < toDestroy.size(); i++)
	{
		m_pPhysicsManager->RemoveRigidbody(dynamic_cast<GameObject*>(toDestroy[i])->GetComponent<RigidbodyComponent>());
		m_Objects.erase(std::find(m_Objects.begin(), m_Objects.end(), toDestroy[i]));
		delete toDestroy[i];
	}
}

