#include "MiniginPCH.h"
#include "SceneObject.h"

void King::SceneObject::Initialize()
{
}

void King::SceneObject::EarlyUpdate()
{
}

void King::SceneObject::Update()
{
}

void King::SceneObject::Render() const
{
}

void King::SceneObject::SetInitialized(bool init)
{
	m_Initialized = init;
}

bool King::SceneObject::IsInitialized() const
{
	return m_Initialized;
}

void King::SceneObject::Destroy()
{
	m_Destroyed = true;
}

bool King::SceneObject::IsDestroyed() const
{
	return m_Destroyed;
}

King::SceneObject::SceneObject()
	: m_Initialized{ false }
	, m_Destroyed{ false }
{
}
