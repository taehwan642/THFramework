#include "DXUT.h"
#include "Player.h"
#include "UIPack.h"
#include "Item.h"
#include "TileMapManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Chest.h"
#include "Effect.h"
#include "SoundManager.h"
#include "Monster1.h"
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

	uipack = new UIPack;
	uipack->Init(p, &coolTime);
	// UI
	// 적

	for (auto iter : tm.monsterpos)
	{
		Monster* m;
		switch (iter.type)
		{
		case MONSTER1:
			m = new Monster1;
			m->player = p;
			m->scale = { tm.blockScale, tm.blockScale };
			break;
			// 
		default:
			break;
		}
		m->position = iter.position;
		monsters.push_back(m);
	}
	

	for (auto iter : tm.chestpos)
	{
		Chest* c = new Chest;
		c->position = iter;
		c->scale = { tm.blockScale, tm.blockScale };
		chests.push_back(c);
	}

	ItemManager::GetInstance().pl = p;
	ItemManager::GetInstance().Create();

	BManager::GetInstance().player = p;
	BManager::GetInstance().Create();

	EManager::GetInstance().Create();

	SoundManager::GetInstance().Play(L"bgm", 0, true);
}

void Stage1::Update()
{
	if(DXUTWasKeyPressed('B'))
		ItemManager::GetInstance().Spawn({ screenwidth / 2, screenheight / 2 });

	Camera& cam = Camera::GetInstance();
	D3DXVec2Lerp(&cam.camPos, &cam.camPos, &p->position, DXUTGetElapsedTime() * 2);

	coolTime -= DXUTGetElapsedTime();
	uipack->Update();
}

void Stage1::Exit()
{
	uipack->Delete();
	delete p;
	ItemManager::GetInstance().Delete();

	TileMapManager::GetInstance().DeleteBlocks();
	BManager::GetInstance().Delete();
	EManager::GetInstance().Delete();

	for (auto iter : chests)
		delete iter;
	chests.clear();
}
