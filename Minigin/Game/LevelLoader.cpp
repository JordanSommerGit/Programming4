#include "LevelLoader.h"
#include <fstream>
#include "GameObject.h"
#include "Scene.h"
#include "Character.h"
#include "Bounds.h"
#include "Platform.h"
#include "Zenchan.h"
#include "Maita.h"
#include "SpriteRenderComponent.h"

King::LevelLoader::LevelLoader(std::string filename)
	: m_Filename{ filename }
{
}

void King::LevelLoader::Initialize()
{
	std::ifstream fileStream{m_Filename, std::ifstream::in};

	std::string imageName = m_Filename.substr(m_Filename.find("Level"), 6) + "Background.png";
	AddLevel(imageName);

	if (!fileStream.is_open())
	{
		return;
	}

	while (!fileStream.eof())
	{
		std::string line = "";
		std::getline(fileStream, line);
		int valueCount = 0;
		std::string value = "";
		char prefix = ' ';
		float posX = 0;
		float posY = 0;
		float width = 0;
		float height = 0;
		for (size_t i = 0; i < line.size(); i++)
		{
			if (i == 0)
			{
				prefix = line[i];
			}
			else if (line[i] == ',')
			{
				switch (valueCount)
				{
				case 0:
					posX = std::stof(value);
					break;
				case 1:
					posY = std::stof(value);
					break;
				case 2:
					width = std::stof(value);
					break;
				case 3:
					height = std::stof(value);
					break;
				}
				value = "";
				valueCount++;
			}
			else
			{
				value += line[i];
			}
		}

		switch (prefix)
		{
		case 'C':
			AddCharacter(posX, posY);
			break;
		case 'B':
			AddBounds(width, height, posX, posY);
			break;
		case 'P':
			AddPlatform(width, height, posX, posY);
			break;
		case 'Z':
			AddZenchan(posX, posY);
			break;
		case 'M':
			AddMaita(posX, posY);
			break;
		}
	}
}

King::Character* King::LevelLoader::GetCharacter() const
{
	return m_pCharacter;
}

void King::LevelLoader::AddLevel(std::string filename)
{
	auto mapGo = new GameObject();
	auto pSprite = new SpriteRenderComponent();
	pSprite->SetSprite(filename, 512, 424, 1, 1, 1);
	mapGo->AddComponent(pSprite);
	GetScene()->Add(mapGo);
}

void King::LevelLoader::AddCharacter(float posX, float posY)
{
	auto character = new Character();
	m_pCharacter = character;
	character->SetPosition(posX, posY);
	GetScene()->Add(character);
}

void King::LevelLoader::AddBounds(float width, float height, float posX, float posY)
{
	auto pGo = new Bounds(width, height);
	pGo->SetPosition(posX, posY);
	GetScene()->Add(pGo);
}

void King::LevelLoader::AddPlatform(float width, float height, float posX, float posY)
{

	auto pGo = new Platform(width, height);
	pGo->SetPosition(posX, posY);
	GetScene()->Add(pGo);
}

void King::LevelLoader::AddZenchan(float posX, float posY)
{
	auto pEnemy = new Zenchan();
	pEnemy->SetPosition(posX, posY);
	GetScene()->Add(pEnemy);
}

void King::LevelLoader::AddMaita(float posX, float posY)
{
	auto pEnemy = new Maita();
	pEnemy->SetPosition(posX, posY);
	GetScene()->Add(pEnemy);
}
