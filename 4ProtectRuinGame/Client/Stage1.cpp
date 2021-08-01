#include "DXUT.h"
#include "Camera.h"
#include "Stage1.h"

void 
Stage1::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	cam.SetCameraSize(2.f);

	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.LoadBlocks();
	
	player = new Player();
	player->collider->position = tmm.playerPos;

	mm.player = player;
	mm.CreateMonster();
	for (auto& iter : tmm.enemyPos)
	{
		mm.SpawnMonster(MonsterTag::OCTOPUS, iter);
	}

	minimap = new Minimap;
}

void 
Stage1::Update()
{
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
Stage1::Exit()
{
	delete player;
	mm.DeleteMonster();
	delete minimap;
}
