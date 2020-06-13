#pragma once
#include "Enemy.h"

namespace King
{

	class Maita : public Enemy
	{
	public:
		Maita();
		virtual ~Maita() = default;

		Maita(const Maita& other) = delete;
		Maita(Maita&& other) = delete;
		Maita& operator=(const Maita& other) = delete;
		Maita& operator=(Maita&& other) = delete;

		void Initialize() override;
		void Update() override;
	private:
	};
}

