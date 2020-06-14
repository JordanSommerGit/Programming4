#pragma once
#include "Singleton.h"
#include <map>
#include <XInput.h>
#include <SDL.h>
#include <string>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

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
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int controller);
		glm::vec3 GetLeftstick(DWORD controller = 0);
		SDL_Event GetEvent() const;

		void AddControllerCommand(DWORD controller, ControllerButton button, Command* pCommand);
		void AddKeyboardCommand(SDL_Scancode button, Command* pCommand);
		bool ExectueCommand(DWORD controller, ControllerButton button);
		bool ExectueCommand(SDL_Scancode key);
	private:
		DWORD m_CurrentController{};
		XINPUT_STATE m_ControllerState[XUSER_MAX_COUNT]{};
		SDL_Event m_Event;
		std::map<DWORD,std::map<ControllerButton, Command*>> m_pControllerCommands;
		std::map<SDL_Scancode, Command*> m_pKeyboardCommands;
	};

}
