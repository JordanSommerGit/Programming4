#pragma once
#include "Character.h"
#include "Command.h"

namespace King
{
	class Bob : public Character
	{
	public:
		class JumpCommand : public Command
		{
		public:
			JumpCommand(Bob* character)
			{
				m_pCharacter = character;
			}
			virtual void Execute() override
			{
				m_pCharacter->Jump();
			}
		private:
			Bob* m_pCharacter;
		};

		class ShootCommand : public Command
		{
		public:
			ShootCommand(Bob* character)
			{
				m_pCharacter = character;
			}
			virtual void Execute() override
			{
				m_pCharacter->Shoot();
			}
		private:
			Bob* m_pCharacter;
		};

		Bob();
		virtual ~Bob() = default;

		Bob(const Bob& other) = delete;
		Bob(Bob&& other) = delete;
		Bob& operator=(const Bob& other) = delete;
		Bob& operator=(Bob&& other) = delete;

		void Initialize() override;
		void Update() override;
	protected:
		bool m_LeftDown;
		bool m_RightDown;
		bool m_UpDown;
		bool m_LDown;

		void Jump();
		void Shoot();
	};
}