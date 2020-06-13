#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void King::Renderer::Init(SDL_Window * window)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void King::Renderer::Render() const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void King::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void King::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void King::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void King::Renderer::RenderTexture(const Texture2D& texture, float DestX, float DestY, float DestWidth, float DestHeight, float SrcX, float SrcY, float SrcWidth, float SrcHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(DestX);
	dst.y = static_cast<int>(DestY);
	dst.w = static_cast<int>(DestWidth);
	dst.h = static_cast<int>(DestHeight);
	SDL_Rect src{};
	src.x = static_cast<int>(SrcX);
	src.y = static_cast<int>(SrcY);
	src.w = static_cast<int>(SrcWidth);
	src.h = static_cast<int>(SrcHeight);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void King::Renderer::RenderRect(float left, float bottom, float width, float height)
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), 0, 255, 0, 255);
	SDL_Rect dst;
	dst.x = static_cast<int>(left);
	dst.y = static_cast<int>(bottom);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderDrawRect(GetSDLRenderer(), &dst);
}
