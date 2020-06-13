#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <algorithm>
#include <vector>

namespace King
{
	class Texture2D;
	class ColliderComponent;
	class GameObject : public SceneObject
	{
	public:
		void RootInitialize() override;
		void RootEarlyUpdate() override;
		void RootUpdate() override;
		void RootRender() const override;

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

		virtual void OnTriggerEnter(ColliderComponent* other);
		virtual void OnTriggerExit(ColliderComponent* other);
		virtual void OnTriggerStay(ColliderComponent* other);

		template<class T>
		T* GetComponent()
		{
			for (auto* component : m_Components)
			{
				if (typeid(T) == typeid(*component))
				{
					return static_cast<T*>(component);
				}
			}
			return nullptr;
		}

		void SetPosition(float x, float y);
		Transform* GetTransform();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<Component*> m_Components;
	};
}
