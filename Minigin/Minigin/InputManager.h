#pragma once
#include "Singleton.h"
#include <map>
#include <XInput.h>
#include <SDL.h>

namespace King
{
	class Command;
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
		bool IsPressed(ControllerButton button);
		SDL_Event GetEvent() const;

		void AddControllerCommand(ControllerButton button, Command* pCommand);
		void AddKeyboardCommand(char button, Command* pCommand);
		bool ExectueCommand(ControllerButton button);
		bool ExectueCommand(char key);
	private:
		XINPUT_STATE m_CurrentState{};
		SDL_Event m_Event;
		std::map<ControllerButton, Command*> m_pControllerCommands;
		std::map<char, Command*> m_pKeyboardCommands;
	};

}
