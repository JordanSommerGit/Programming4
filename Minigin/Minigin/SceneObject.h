#pragma once
namespace King
{
	class Scene;
	class SceneObject
	{
	public:
		virtual void Initialize();
		virtual void EarlyUpdate();
		virtual void Update();
		virtual void Render() const;

		virtual void RootInitialize() = 0;
		virtual void RootEarlyUpdate() = 0;
		virtual void RootUpdate() = 0;
		virtual void RootRender() const = 0;

		SceneObject();
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		void SetScene(Scene* pScene) { m_pScene = pScene; };
		Scene* GetScene() { return m_pScene; };

		void SetInitialized(bool init);
		bool IsInitialized() const;

		void Destroy();
		bool IsDestroyed() const;

	private:
		Scene* m_pScene;

	protected:
		bool m_Initialized;
		bool m_Destroyed;
	};
}
