#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "SpriteRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"

King::SpriteRenderComponent::SpriteRenderComponent()
	: m_Sprite(nullptr)
	, m_Rows( 0 )
	, m_Columns( 0 )
	, m_Width( 0 )
	, m_Height( 0 )
	, m_CurrentAnimationTime( 0.f )
	, m_AnimationTime( 0.1f )
	, m_FrameIndex( 0 )
	, m_FrameCount( 0 )
	, m_StartRow( 0 )
	, m_StartColumn( 0 )
	, m_FrameIncrease( 1 )
{

}

void King::SpriteRenderComponent::Update()
{
	if (m_Sprite != nullptr)
	{
		m_CurrentAnimationTime += Time::GetInstance().GetElapsed();

		if (m_CurrentAnimationTime > m_AnimationTime)
		{
			m_FrameIndex += m_FrameIncrease;
			m_FrameIndex %= m_FrameCount;
			m_CurrentAnimationTime = 0.f;
		}
	}
}

void King::SpriteRenderComponent::Render() const
{
	if (m_Sprite != nullptr)
	{
		const auto pos = pGameObject->GetTransform()->GetPosition();

		int srcWidth = m_TextWidth / m_Columns;
		int srcHeight = m_TextHeight / m_Rows;
		int srcX = (m_StartColumn + m_FrameIndex) % m_Columns * srcWidth;
		int srcY = (m_StartRow + m_FrameIndex / m_Columns) * srcHeight;
		Renderer::GetInstance().RenderTexture(*m_Sprite, pos.x, pos.y, (float)m_Width, (float)m_Height, (float)srcX, (float)srcY, (float)srcWidth, (float)srcHeight);
	}
}

void King::SpriteRenderComponent::SetSprite(const std::string& filename, int width, int height, int rows, int columns, int frameCount)
{
	m_Sprite = ResourceManager::GetInstance().LoadTexture(filename);
	m_Rows = rows;
	m_Columns = columns;
	m_FrameCount = frameCount;
	m_Width = width;
	m_Height = height;
	UINT32 format;
	int access;
	int w;
	int h;
	SDL_QueryTexture((*m_Sprite).GetSDLTexture(), &format, &access, &w, &h);
	m_TextWidth = w;
	m_TextHeight = h;
}

void King::SpriteRenderComponent::SetSprite(const std::string& filename, int width, int height, int rows, int columns, int frameCount, int startRow)
{
	SetSprite(filename, width, height, rows, columns, frameCount);
	m_StartRow = startRow;
}

void King::SpriteRenderComponent::SetStartRow(int row)
{
	m_StartRow = row;
}

void King::SpriteRenderComponent::SetStartColumn(int column)
{
	m_StartColumn = column;
}

void King::SpriteRenderComponent::SetFrameCount(int count)
{
	m_FrameCount = count;
}

void King::SpriteRenderComponent::SetFrameIncrease(int increase)
{
	m_FrameIncrease = increase;
}

void King::SpriteRenderComponent::SetAnimationTime(float time)
{
	m_AnimationTime = time;
}

int King::SpriteRenderComponent::GetFrameIndex() const
{
	return m_FrameIndex;
}
