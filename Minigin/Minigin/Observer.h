#pragma once
#include <string>

namespace King
{

	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;

		virtual void OnNotify(GameObject* source, std::string event);
	};
}