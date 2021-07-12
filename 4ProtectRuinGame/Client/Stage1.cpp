#include "DXUT.h"
#include "Camera.h"
#include "Stage1.h"

void 
Stage1::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	player = new Player();
}

void 
Stage1::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();

	Camera& cam = Camera::GetInstance();

	Vec2 camPos = cam.GetPosition();

	if (DXUTIsKeyDown('W'))
	{
		camPos.y -= 500.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('S'))
	{
		camPos.y += 500.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('A'))
	{
		camPos.x -= 500.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('D'))
	{
		camPos.x += 500.f * DXUTGetElapsedTime();
	}

	cam.SetPosition(camPos);

	if (DXUTWasKeyPressed('P'))
		tmm.LoadBlocks();
}

void 
Stage1::Exit()
{
	delete player;
}
