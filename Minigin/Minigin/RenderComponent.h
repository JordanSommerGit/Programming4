#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "Component.h"

namespace King
{
	class Texture2D;
	class RenderComponent final : public Component
	{
	public:
		void Render() const override;

		void SetTexture(const std::string& filename);

		explicit RenderComponent();
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}
