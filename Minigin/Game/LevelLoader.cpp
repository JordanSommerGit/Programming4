#include "LevelLoader.h"
#include <fstream>
#include "GameObject.h"
#include "Scene.h"
#include "Bub.h"
#include "Bob.h"
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
		case 'F':
			AddBub(posX, posY);
			break;
		case 'S':
			AddBob(posX, posY);
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

King::Character* King::LevelLoader::GetBub() const
{
	return m_pBub;
}

King::Character* King::LevelLoader::GetBob() const
{
	return m_pBob;
}

void King::LevelLoader::SpawnBob()
{
	auto bob = new Bob();
	m_pBob = bob;
	bob->SetPosition(m_BobPosX, m_BobPosY);
	GetScene()->Add(bob);
}

void King::LevelLoader::AddLevel(std::string filename)
{
	auto mapGo = new GameObject();
	auto pSprite = new SpriteRenderComponent();
	pSprite->SetSprite(filename, 512, 424, 1, 1, 1);
	mapGo->AddComponent(pSprite);
	GetScene()->Add(mapGo);
}

void King::LevelLoader::AddBub(float posX, float posY)
{
	auto bub = new Bub();
	m_pBub = bub;
	bub->SetPosition(posX, posY);
	GetScene()->Add(bub);
}

void King::LevelLoader::AddBob(float posX, float posY)
{
	m_BobPosX = posX;
	m_BobPosY = posY;
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
