#include "DXUT.h"
#include "Camera.h"
#include "Stage.h"

std::vector<Map*> Stage::stages = std::vector<Map*>();

void Stage::CheckPlayerInDoor()
{
	if (true == stages[currentStageindex]->isCleared)
	{
		RECT temp;
		if (IntersectRect(&temp, &player->collider->GetRect(), &door->GetRect()))
		{
			if (DXUTWasKeyPressed('W'))
			{
				++currentStageindex;
				TileMapManager& tmm = TileMapManager::GetInstance();
				tmm.LoadBlocks(stages[currentStageindex]->mapName);
				LoadPosition(tmm);
			}
		}
	}
}

void Stage::LoadPosition(const TileMapManager& tmm)
{
	player->collider->position = tmm.playerPos;
	player->position = tmm.playerPos;

	for (auto& iter : tmm.enemyPos)
	{
		switch (iter.first)
		{
		case BlockType::NONE:
			break;
		case BlockType::FLOOR:
			break;
		case BlockType::OBSTICLE:
			break;
		case BlockType::PLAYER:
			break;
		case BlockType::OCTOPUS:
			mm.SpawnMonster(MonsterTag::OCTOPUS, iter.second, 1);
			break;
		case BlockType::DOOR:
			break;
		case BlockType::BOSS:
			mm.SpawnMonster(MonsterTag::BOSS, iter.second, 1);
			break;
		default:
			break;
		}
		
	}

	door->position = tmm.doorPos;

}

void
Stage::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	cam.SetCameraSize(2.f);

	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.LoadBlocks(stages[currentStageindex]->mapName);

	player = new Player();
	

	mm.player = player;
	mm.CreateMonster();
	

	minimap = new Minimap;

	door = new AniSprite;
	door->SetTexture(L"door1.png");

	LoadPosition(tmm);
}

void
Stage::Update()
{
	stages[currentStageindex]->isCleared = true;
	for (auto& iter : mm.monsters)
	{
		if (nullptr != iter && iter->isactive == true)
			stages[currentStageindex]->isCleared = false;
	}

	CheckPlayerInDoor();

	Camera& cam = Camera::GetInstance();

	Vec2 camPos = cam.GetPosition();

	if (DXUTIsKeyDown(VK_UP))
	{
		camPos.y -= 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_DOWN))
	{
		camPos.y += 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_LEFT))
	{
		camPos.x -= 1000.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown(VK_RIGHT))
	{
		camPos.x += 1000.f * DXUTGetElapsedTime();
	}

	cam.SetPosition(camPos);

	minimap->Update();
}

void
Stage::Exit()
{
	delete player;
	mm.DeleteMonster();
	delete minimap;

	for (auto& iter : stages)
		delete iter;

	delete door;
}
