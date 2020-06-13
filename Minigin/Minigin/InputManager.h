#pragma once
#include <XInput.h>
#include <SDL.h>
#include "Singleton.h"

namespace King
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonDPadDown,
		ButtonDPadRight,
		ButtonDPadLeft,
		ButtonDPadUp
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		SDL_Event GetEvent() const;
	private:
		XINPUT_STATE m_CurrentState{};
		SDL_Event m_Event;
	};

}
