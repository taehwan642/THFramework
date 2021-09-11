#include "DXUT.h"
#include "Player.h"
#include "UIPack.h"
#include "Item.h"
#include "TileMapManager.h"
#include "Stage1.h"

void Stage1::Init()
{
	// 플레이어
	TileMapManager& tm = TileMapManager::GetInstance();
	tm.LoadObject("mapobj.txt");
	tm.LoadBlocks("mapblock.txt");

	p = new Player;
	p->position = tm.playerpos;
	p->scale ={ tm.blockScale, tm.blockScale };
	p->SetTexture(L"player (1).png");

	uipack = new UIPack;
	uipack->Init(p, &coolTime);
	// UI
	// 적

	ItemManager::GetInstance().pl = p;
	ItemManager::GetInstance().Create();
}

void Stage1::Update()
{
	if(DXUTWasKeyPressed('B'))
		ItemManager::GetInstance().Spawn({ screenwidth / 2, screenheight / 2 });

	coolTime -= DXUTGetElapsedTime();
	uipack->Update();
}

void Stage1::Exit()
{
	uipack->Delete();
	delete p;
	ItemManager::GetInstance().Delete();

	TileMapManager::GetInstance().DeleteBlocks();
}
