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
		tm.SaveObject("mapobj.txt");
		tm.SaveBlocks("mapblock.txt");
	}
	if (DXUTWasKeyPressed('O'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void TilemapScene::Exit()
{
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.DeleteBlocks();
}
