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

		void AddChild(GameObject* component);
		void RemoveChild(GameObject* component);

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

		template<class T>
		std::vector<T*> GetComponents(bool inChildren = false)
		{
			std::vector<T*> output;
			for (auto* component : m_Components)
			{
				if (typeid(T) == typeid(*component))
				{
					output.push_back(static_cast<T*>(component));
				}
			}

			if (!inChildren)
			{
				return output;
			}

			for (GameObject* pChild : m_Children)
			{
				std::vector<T*> childComponents = pChild->GetComponents<T>();
				for (auto* component : childComponents)
				{
					if (typeid(T) == typeid(*component))
					{
						output.push_back(static_cast<T*>(component));
					}
				}
			}

			return output;
		}

		void SetPosition(float x, float y);
		Transform* GetTransform();

		GameObject* GetParent() const;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_Transform;
		std::vector<Component*> m_Components;
		GameObject* m_pParent;
		std::vector<GameObject*> m_Children;
	};
}
