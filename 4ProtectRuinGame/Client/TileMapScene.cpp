#include "DXUT.h"
#include "SceneManager.h"
#include "TileMapScene.h"

void 
TileMapScene::Init()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.Initialize();
}

void 
TileMapScene::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.UpdateManager();

	if (DXUTWasKeyPressed('O'))
		tmm.SaveBlocks();

	if (DXUTWasKeyPressed('M'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void 
TileMapScene::Exit()
{

}
