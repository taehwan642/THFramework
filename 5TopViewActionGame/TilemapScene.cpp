#include "DXUT.h"
#include "TileMapManager.h"
#include "SceneManager.h"
#include "TilemapScene.h"

void TilemapScene::Init()
{
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.Initialize();
}

void TilemapScene::Update()
{
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.UpdateManager();

	Camera& cam = Camera::GetInstance();

	if (DXUTIsKeyDown('W'))
	{
		cam.camPos.y -= 500.f * DXUTGetElapsedTime();
	}

	if (DXUTIsKeyDown('A'))
	{
		cam.camPos.x -= 500.f * DXUTGetElapsedTime();
	}

	if (DXUTIsKeyDown('S'))
	{
		cam.camPos.y += 500.f * DXUTGetElapsedTime();
	}

	if (DXUTIsKeyDown('D'))
	{
		cam.camPos.x += 500.f * DXUTGetElapsedTime();
	}


	if (DXUTWasKeyPressed('I'))
	{
		tm.SaveObject("mapobj2.txt");
		tm.SaveBlocks("mapblock2.txt");
	}

	if (DXUTWasKeyPressed('U'))
	{
		tm.UpdateBlocks("mapblock2.txt");
		tm.UpdateObject("mapobj2.txt");
	}

	if (DXUTWasKeyPressed('O'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void TilemapScene::Exit()
{
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.DeleteBlocks();
}
