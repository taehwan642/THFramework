#include "DXUT.h"
#include "MenuScene.h"

void 
MenuScene::Init()
{
}

void 
MenuScene::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.CheckMouseCollision();
	tmm.UpdateManager();
	
}

void 
MenuScene::Exit()
{
}
