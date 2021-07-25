#include "DXUT.h"
#include "Camera.h"
#include "Stage1.h"

void 
Stage1::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	player = new Player();

	mm.player = player;
	mm.CreateMonster();
}

void 
Stage1::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();

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

	if (DXUTWasKeyPressed('P'))
		tmm.LoadBlocks();

	if (DXUTWasKeyPressed('Z'))
		mm.SpawnMonster(MonsterTag::OCTOPUS, camPos);
}

void 
Stage1::Exit()
{
	delete player;
	mm.DeleteMonster();
}
