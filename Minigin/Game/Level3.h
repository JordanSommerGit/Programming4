#pragma once
#include "Scene.h"

using namespace King;

class Level3 : public Scene
{
public:
	Level3();
	~Level3() = default;

	void Initialize() override;
	void EarlyUpdate() override;
	void Update() override;

	Level3(const Level3& other) = delete;
	Level3(Level3&& other) = delete;
	Level3& operator=(const Level3& other) = delete;
	Level3& operator=(Level3&& other) = delete;
};