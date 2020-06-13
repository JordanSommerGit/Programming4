#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"

King::RenderComponent::RenderComponent()
	: m_Texture(nullptr)
{ }

void King::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = pGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void King::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}


