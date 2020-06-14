#pragma once
#include "Singleton.h"

namespace King
{
	class Observer;
	class GameObject;
	class EventSystem : public Singleton<EventSystem>
	{
	public:
		~EventSystem();
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		template<class T>
		T* GetObserver()
		{
			for (auto* pObserver : pObservers)
			{
				if (typeid(T) == typeid(*pObserver))
				{
					return static_cast<T*>(pObserver);
				}
			}
			return nullptr;
		}

		void Notify(GameObject* source, std::string event);
	private:
		std::vector<Observer*> pObservers;
	};
}