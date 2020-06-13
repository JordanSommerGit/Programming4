#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

King::TextRenderComponent::TextRenderComponent()
	: m_NeedsUpdate(true), m_Text(""), m_Font(nullptr), m_Texture(nullptr)
{ }

void King::TextRenderComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void King::TextRenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void King::TextRenderComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void King::TextRenderComponent::SetFont(std::shared_ptr<Font> font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}


