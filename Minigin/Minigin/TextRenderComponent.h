#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "Component.h"

namespace King
{
	class GameObject;
	class Font;
	class Texture2D;
	class TextRenderComponent final : public Component
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);

		explicit TextRenderComponent();
		virtual ~TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other) = delete;
		TextRenderComponent(TextRenderComponent&& other) = delete;
		TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
		TextRenderComponent& operator=(TextRenderComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
