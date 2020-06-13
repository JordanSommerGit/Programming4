#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

King::GameObject::GameObject()
	: m_pParent{ nullptr }
{
	m_Transform.SetGameObject(this);
}

King::GameObject::~GameObject()
{
	for (Component* component : m_Components)
	{
		delete component;
	}
}

void King::GameObject::RootInitialize()
{
	for (Component* component : m_Components)
	{
		component->Initialize();
	}
	m_Initialized = true;
}

void King::GameObject::RootEarlyUpdate()
{
	for (Component* component : m_Components)
	{
		component->EarlyUpdate();
	}
}

void King::GameObject::RootUpdate()
{
	for (Component* component : m_Components)
	{
		component->Update();
	}
}

void King::GameObject::RootRender() const
{
	for (Component* component : m_Components)
	{
		component->Render();
	}
}


void King::GameObject::AddComponent(Component* component)
{
	component->pGameObject = this;
	m_Components.push_back(component);
}

void King::GameObject::RemoveComponent(Component* component)
{
	if (component != nullptr)
	{
		m_Components.erase(std::find(m_Components.begin(), m_Components.end(), component));
	}
}

void King::GameObject::AddChild(GameObject* child)
{
	child->m_pParent = this;
	GetScene()->Add(child);
	m_Children.push_back(child);
}

void King::GameObject::RemoveChild(GameObject* child)
{
	if (child != nullptr)
	{
		m_Children.erase(std::find(m_Children.begin(), m_Children.end(), child));
	}
}

void King::GameObject::OnTriggerEnter(ColliderComponent*)
{
}

void King::GameObject::OnTriggerExit(ColliderComponent*)
{

}

void King::GameObject::OnTriggerStay(ColliderComponent*)
{
}

void King::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

King::Transform* King::GameObject::GetTransform()
{
	return &m_Transform;
}

King::GameObject* King::GameObject::GetParent() const
{
	return m_pParent;
}
