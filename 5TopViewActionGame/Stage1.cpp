#include "DXUT.h"
#include "Player.h"
#include "UIPack.h"
#include "Item.h"
#include "Stage1.h"

void Stage1::Init()
{
	// 플레이어
	
	p = new Player;
	p->position = { screenwidth / 2, screenheight / 2 };
	p->SetTexture(L"hit (1).png");

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
}
