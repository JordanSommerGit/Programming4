#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <vector>

namespace King
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(Scene* pScene);
		void SetActiveScene(const std::string& name);

		void Initialize();
		void EarlyUpdate();
		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		~SceneManager();
		std::vector<Scene*> m_Scenes;
		Scene* m_pActiveScene;
	};
}
