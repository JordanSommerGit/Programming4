#pragma once

namespace King
{
	class GameObject;

	class Component
	{
	public:
		Component() = default;

		virtual void Initialize();
		virtual void EarlyUpdate();
		virtual void Update();
		virtual void Render() const;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		GameObject* pGameObject;
	protected:

	private:
	};
}