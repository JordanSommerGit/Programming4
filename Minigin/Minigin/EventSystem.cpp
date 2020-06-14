#include "MiniginPCH.h"
#include "EventSystem.h"
#include "Observer.h"
#include "GameObject.h"
#include <vector>

King::EventSystem::~EventSystem()
{
	for (Observer* pObserver : pObservers)
	{
		delete pObserver;
		pObserver = nullptr;
	}
}

void King::EventSystem::AddObserver(Observer* pObserver)
{
	pObservers.push_back(pObserver);
}

void King::EventSystem::RemoveObserver(Observer* pObserver)
{
	pObservers.erase(std::find(pObservers.begin(), pObservers.end(), pObserver));
}

void King::EventSystem::Notify(GameObject* source, std::string event)
{
	for (Observer* pObserver : pObservers)
	{
		pObserver->OnNotify(source, event);
	}
}
