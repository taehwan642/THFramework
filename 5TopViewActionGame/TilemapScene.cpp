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

	if (DXUTWasKeyPressed('I'))
		tm.SaveBlocks("map1.txt");
	if (DXUTWasKeyPressed('O'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void TilemapScene::Exit()
{
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.DeleteBlocks();
}
