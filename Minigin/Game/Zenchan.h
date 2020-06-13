#pragma once
#include "Enemy.h"

namespace King
{

	class Zenchan : public Enemy
	{
	public:
		Zenchan();
		virtual ~Zenchan() = default;

		Zenchan(const Zenchan& other) = delete;
		Zenchan(Zenchan&& other) = delete;
		Zenchan& operator=(const Zenchan& other) = delete;
		Zenchan& operator=(Zenchan&& other) = delete;

		void Initialize() override;
		void Update() override;
	private:
	};
}