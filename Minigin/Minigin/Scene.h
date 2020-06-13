#pragma once
#include "SceneManager.h"

namespace King
{
	class PhysicsManager;
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(SceneObject* object);

		virtual void Initialize();
		virtual void EarlyUpdate();
		virtual void Update();
		virtual void Render() const;

		void RootInitialize();
		void RootEarlyUpdate();
		void RootUpdate();
		void RootRender();

		void CleanUp();

		explicit Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		PhysicsManager* GetPhysicsManager();
	private: 

		std::string m_Name;
		std::vector<SceneObject*> m_Objects{};
		PhysicsManager* m_pPhysicsManager;

		static unsigned int m_IdCounter; 
	};

}