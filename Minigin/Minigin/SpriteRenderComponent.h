#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "Component.h"

namespace King
{
	class Texture2D;
	class SpriteRenderComponent final : public Component
	{
	public:
		void Update() override;
		void Render() const override;

		void SetSprite(const std::string& filename, int width, int height, int rows, int columns, int frameCount);
		void SetSprite(const std::string& filename, int width, int height, int rows, int columns, int frameCount, int startRow);

		void SetStartRow(int row);
		void SetFrameCount(int count);
		void SetFrameIncrease(int increase);
		void SetAnimationTime(float time);

		int GetFrameIndex() const;

		explicit SpriteRenderComponent();
		virtual ~SpriteRenderComponent() = default;
		SpriteRenderComponent(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent(SpriteRenderComponent&& other) = delete;
		SpriteRenderComponent& operator=(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent& operator=(SpriteRenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_Sprite;
		int m_Width;
		int m_Height;
		int m_TextHeight;
		int m_TextWidth;
		int m_Rows;
		int m_Columns;
		int m_FrameCount;
		int m_StartRow;
		float m_CurrentAnimationTime;
		float m_AnimationTime;
		int m_FrameIndex;;
		int m_FrameIncrease;
	};
}

