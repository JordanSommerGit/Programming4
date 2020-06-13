#pragma once
#include "Scene.h"

using namespace King;

class Level2 : public Scene
{
public:
	Level2();
	~Level2() = default;

	void Initialize() override;
	void EarlyUpdate() override;
	void Update() override;

	Level2(const Level2& other) = delete;
	Level2(Level2&& other) = delete;
	Level2& operator=(const Level2& other) = delete;
	Level2& operator=(Level2&& other) = delete;
};