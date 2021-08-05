#include "DXUT.h"
#include "Camera.h"
#include "Stage.h"
std::vector<Map*> Stage::stages = std::vector<Map*>();

void
Stage::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	cam.SetCameraSize(2.f);

	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.LoadBlocks(stages[currentStageindex]->mapName);

	player = new Player();
	player->collider->position = tmm.playerPos;
	player->position = tmm.playerPos;

	mm.player = player;
	mm.CreateMonster();
	for (auto& iter : tmm.enemyPos)
	{
		mm.SpawnMonster(MonsterTag::OCTOPUS, iter);
	}

	minimap = new Minimap;
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

	std::cout << stages[currentStageindex]->isCleared << std::endl;

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
}
