#pragma once
#include "SpriteRenderComponent.h"

namespace King
{
	class BubAnimationState
	{
	public:
		virtual void Animate(SpriteRenderComponent*)
		{
		}
	};

	class BubRunningLeft : public BubAnimationState
	{
		void Animate(SpriteRenderComponent* sprite) override
		{
			sprite->SetStartRow(1);
		}
	};

	class BubRunningRight : public BubAnimationState
	{
		void Animate(SpriteRenderComponent* sprite) override
		{
			sprite->SetStartRow(0);
		}
	};

	class BubShootingLeft : public BubAnimationState
	{
		void Animate(SpriteRenderComponent* sprite) override
		{
			sprite->SetStartRow(4);
		}
	};

	class BubShootingRight : public BubAnimationState
	{
		void Animate(SpriteRenderComponent* sprite) override
		{
			sprite->SetStartRow(2);
		}
	};
}