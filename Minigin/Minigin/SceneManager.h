#pragma once
#include "Singleton.h"

namespace King
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(std::shared_ptr<Scene> scene);

		void Initialize();
		void EarlyUpdate();
		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
