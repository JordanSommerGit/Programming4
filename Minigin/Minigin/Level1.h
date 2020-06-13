#pragma once
#include "Scene.h"

using namespace King;

class Level1 : public Scene
{
public:
	Level1();
	~Level1() = default;

	void Initialize() override;
	void EarlyUpdate() override;
	void Update() override;

	Level1(const Level1& other) = delete;
	Level1(Level1&& other) = delete;
	Level1& operator=(const Level1& other) = delete;
	Level1& operator=(Level1&& other) = delete;
};