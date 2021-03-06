#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace King
{
	class GameObject;
	class Transform final
	{
	public:
		void SetGameObject(GameObject* pGameObject);
		const glm::vec3 GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);
	private:
		glm::vec3 m_Position;
		GameObject* m_pGameObject;
	};
}
