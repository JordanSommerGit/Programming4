#pragma once
#include "GameObject.h"
#include <string>

namespace King
{
	class Character;
	class Enemy;
	class LevelLoader : public GameObject
	{
	public:
		LevelLoader(std::string filename);
		virtual ~LevelLoader() = default;

		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		void Initialize() override;

		Character* GetCharacter() const;
	private:
		void AddLevel(std::string filename);
		void AddCharacter(float posX, float posY);
		void AddBounds(float width, float height, float posX, float posY);
		void AddPlatform(float width, float height, float posX, float posY);
		void AddZenchan(float posX, float posY);
		void AddMaita(float posX, float posY);

		std::string m_Filename;

		Character* m_pCharacter;
	};
}