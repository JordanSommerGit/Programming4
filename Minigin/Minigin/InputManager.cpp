#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"

bool King::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_Event = e;
		}
		if (e.type == SDL_KEYUP) {
			m_Event = e;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_Event = e;
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			m_Event = e;
		}
	}

	//Commands
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		ExectueCommand(ControllerButton::ButtonA);
	}
	else if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		ExectueCommand(ControllerButton::ButtonB);
	}
	else if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		ExectueCommand(ControllerButton::ButtonX);
	}
	else if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	{
		ExectueCommand(ControllerButton::ButtonY);
	}

	return true;
}

bool King::InputManager::IsPressed(ControllerButton button)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

bool King::InputManager::ExectueCommand(ControllerButton button)
{
	if (m_pControllerCommands.find(button) != m_pControllerCommands.end())
	{
		m_pControllerCommands[button]->Execute();
		return true;
	}
	return false;
}

bool King::InputManager::ExectueCommand(char key)
{
	if (m_pKeyboardCommands.find(key) != m_pKeyboardCommands.end())
	{
		m_pKeyboardCommands[key]->Execute();
		return true;
	}
	return false;
}

SDL_Event King::InputManager::GetEvent() const
{
	return m_Event;
}

void King::InputManager::AddControllerCommand(ControllerButton button, Command* pCommand)
{
	m_pControllerCommands[button] = pCommand;
}

void King::InputManager::AddKeyboardCommand(char button, Command* pCommand)
{
	m_pKeyboardCommands[button] = pCommand;
}

