#pragma once
#include "Character.h"
#include "Command.h"
#include "BubAnimationStates.h"

namespace King
{
	class Bub : public Character
	{
	public:
		class JumpCommand : public Command
		{
		public:
			JumpCommand(Bub* character)
			{
				m_pCharacter = character;
			}
			virtual void Execute() override
			{
				m_pCharacter->Jump();
			}
		private:
			Bub* m_pCharacter;
		};

		class ShootCommand : public Command
		{
		public:
			ShootCommand(Bub* character)
			{
				m_pCharacter = character;
			}
			virtual void Execute() override
			{
				m_pCharacter->Shoot();
			}
		private:
			Bub* m_pCharacter;
		};

		Bub();
		virtual ~Bub() = default;

		Bub(const Bub& other) = delete;
		Bub(Bub&& other) = delete;
		Bub& operator=(const Bub& other) = delete;
		Bub& operator=(Bub&& other) = delete;

		void Initialize() override;
		void Update() override;
	protected:
		BubAnimationState m_AnimationState;

		bool m_ADown;
		bool m_DDown;
		bool m_WDown;
		bool m_FDown;

		void Jump();
		void Shoot();
	};
}