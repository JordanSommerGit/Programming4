#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"

King::InputManager::~InputManager()
{
	std::map<DWORD, std::map<ControllerButton, Command*>>::iterator ccit;
	for (ccit = m_pControllerCommands.begin(); ccit != m_pControllerCommands.end(); ccit++)
	{
		std::map<ControllerButton, Command*>::iterator cit;
		for (cit = ccit->second.begin(); cit != ccit->second.end(); cit++)
		{
			delete cit->second;
			cit->second = nullptr;
		}
	}

	std::map<SDL_Scancode, Command*>::iterator kit;
	for (kit = m_pKeyboardCommands.begin(); kit != m_pKeyboardCommands.end(); kit++)
	{
		delete kit->second;
		kit->second = nullptr;
	}
}

bool King::InputManager::ProcessInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_ControllerState[i], sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i, &m_ControllerState[i]);

		//Commands
		if (m_ControllerState[i].Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			ExectueCommand(i, ControllerButton::ButtonA);
		}
		else if (m_ControllerState[i].Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			ExectueCommand(i, ControllerButton::ButtonB);
		}
		else if (m_ControllerState[i].Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			ExectueCommand(i, ControllerButton::ButtonX);
		}
		else if (m_ControllerState[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			ExectueCommand(i, ControllerButton::ButtonY);
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_Event = e;
			ExectueCommand(e.key.keysym.scancode);
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


	return true;
}

bool King::InputManager::IsPressed(ControllerButton button, int controller)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_ControllerState[controller].Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_ControllerState[controller].Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_ControllerState[controller].Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_ControllerState[controller].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

//source https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers
glm::vec3 King::InputManager::GetLeftstick(DWORD controller)
{
	XINPUT_STATE state = m_ControllerState[controller];

	float LX = state.Gamepad.sThumbLX;
	float LY = state.Gamepad.sThumbLY;

	//determine how far the controller is pushed
	float magnitude = sqrt(LX * LX + LY * LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
		return glm::vec3{};
	}

	return glm::vec3(normalizedLX, normalizedLY, 0);
}

bool King::InputManager::ExectueCommand(DWORD controller, ControllerButton button)
{
	if (m_pControllerCommands[controller].find(button) != m_pControllerCommands[controller].end())
	{
		m_pControllerCommands[controller][button]->Execute();
		return true;
	}
	return false;
}

bool King::InputManager::ExectueCommand(SDL_Scancode key)
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

void King::InputManager::AddControllerCommand(DWORD controller, ControllerButton button, Command* pCommand)
{
	if (m_pControllerCommands[controller].find(button) != m_pControllerCommands[controller].end())
	{
		if (m_pControllerCommands[controller][button] != nullptr)
		{
			delete m_pControllerCommands[controller][button];
		}
		m_pControllerCommands[controller][button] = pCommand;
	}
	else
	{
		m_pControllerCommands[controller][button] = pCommand;
	}
}

void King::InputManager::AddKeyboardCommand(SDL_Scancode button, Command* pCommand)
{
	if (m_pKeyboardCommands.find(button) != m_pKeyboardCommands.end())
	{
		if (m_pKeyboardCommands[button] != nullptr)
		{
			delete m_pKeyboardCommands[button];
		}
		m_pKeyboardCommands[button] = pCommand;
	}
	else
	{
		m_pKeyboardCommands[button] = pCommand;
	}
}

