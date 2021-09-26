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
#include "MonsterSpawner.h"
#include "Door.h"
#include "SceneManager.h"
#include "Button.h"
#include "RankScene.h"
#include "Button.h"
#include "Boss1.h"
#include "MonsterBullet.h"
#include "Stage1.h"

void Stage1::CheatKey()
{
	if (DXUTWasKeyPressed(VK_F1))
	{
		p->invincible = !p->invincible;
	}

	if (DXUTWasKeyPressed(VK_F2))
	{
		p->attackgauge = 10;
	}

	if (DXUTWasKeyPressed(VK_F3))
	{
		for (auto iter : MonsterManager::GetInstance().monsters)
		{
			if (iter == nullptr)
				continue;
			if (iter->isactive == false)
				continue;

			Vec2 dist = iter->position - Camera::GetInstance().camPos;
			float length = D3DXVec2Length(&dist);
			if (length < 700)
			{
				iter->isactive = false;
				iter->hpui->isactive = false;
				iter->hpuibar->isactive = false;
			}
		}
		// 700
	}

	

	if (DXUTWasKeyPressed(VK_F5))
	{
		currentStage = 0;
		door->currentDoorIndex = 0;
		SetMap(door->currentDoorIndex); // 넘길 때
		Initialize(); // 넘어갔을 때
		p->movespeed = 300.f;
		uipack->ScoreActive(false);
		coolTime = TIMECOST;
		difficulty = 1;
	}

	if (DXUTWasKeyPressed(VK_F6))
	{
		currentStage = 1;
		door->currentDoorIndex = stagedatas[0] + 1;
		SetMap(door->currentDoorIndex - 1); // 넘길 때
		Initialize(); // 넘어갔을 때
		p->movespeed = 300.f;
		uipack->ScoreActive(false);
		coolTime = TIMECOST;
		difficulty = 1;
	}

	if (DXUTWasKeyPressed(VK_F7))
	{
		currentStage = 2;
		door->currentDoorIndex = stagedatas[0] + stagedatas[1] + 1;
		SetMap(door->currentDoorIndex - 1); // 넘길 때
		Initialize(); // 넘어갔을 때
		p->movespeed = 300.f;
		uipack->ScoreActive(false);
		coolTime = TIMECOST;
		difficulty = 1;
	}

	if (DXUTWasKeyPressed(VK_F8) || DXUTWasKeyPressed(VK_ESCAPE))
	{
		isPaused = !isPaused;
	}

}

void Stage1::Initialize()
{
	for (auto iter : chests)
		delete iter;
	chests.clear();

	for (auto iter : MonsterManager::GetInstance().monsters)
	{
		if (iter != nullptr)
		{
			iter->position = { -999999, -99999 };
			iter->isactive = false;
			iter->hpui->isactive = false;
			iter->hpuibar->isactive = false;
		}
	}

	for (auto iter : MonsterSpawnerManager::GetInstance().spn)
	{
		iter->isactive = false;
	}

	for (auto iter : ItemManager::GetInstance().items)
	{
		iter->isactive = false;
	}

	TileMapManager& tm = TileMapManager::GetInstance();

	p->position = tm.playerpos;

	for (auto iter : tm.monsterpos)
	{
		if (iter.type == MONSTERSPAWNER)
			MonsterSpawnerManager::GetInstance().Spawn(1, { MONSTER1 }, iter.position, difficulty);
		else
			MonsterManager::GetInstance().Spawn(iter.type, iter.position, difficulty);
	}

	for (auto iter : tm.chestpos)
	{
		Chest* c = new Chest;
		c->position = iter;
		c->scale = { tm.blockScale, tm.blockScale };
		chests.push_back(c);
	}

	door->isOpen = false;
	door->position = tm.doortag.pos;
	door->SetTexture(door->SetDoorTexture(tm.doortag.doortype));
}

void Stage1::SetMap(int index)
{
	TileMapManager& tm = TileMapManager::GetInstance();

	tm.LoadObject(mapTXTdata[index].objTXT);
	tm.LoadBlocks(mapTXTdata[index].blockTXT);
}

void Stage1::Init()
{
	// 플레이어
	TileMapManager& tm = TileMapManager::GetInstance();

	MapTXTData data;
	data.blockTXT = "mapblock.txt";
	data.objTXT = "mapobj.txt";
	mapTXTdata.push_back(data);

	data.blockTXT = "mapblock2.txt";
	data.objTXT = "mapobj2.txt";
	mapTXTdata.push_back(data);

	data.blockTXT = "mapblock4.txt";
	data.objTXT = "mapobj4.txt";
	mapTXTdata.push_back(data);

	data.blockTXT = "mapblock3.txt";
	data.objTXT = "mapobj3.txt";
	mapTXTdata.push_back(data);

	SetMap(0);

	p = new Player;
	p->scale = { tm.blockScale, tm.blockScale };

	uipack = new UIPack;
	uipack->Init(p, &coolTime);

	MonsterManager::GetInstance().Create();
	MonsterManager::GetInstance().p = p;
	MonsterSpawnerManager::GetInstance().Create();

	door = new Door;

	ItemManager::GetInstance().pl = p;
	ItemManager::GetInstance().Create();

	BManager::GetInstance().player = p;
	BManager::GetInstance().Create();

	EManager::GetInstance().Create();

	SoundManager::GetInstance().Play(L"bgm", 0, true);

	currentStage = 0;
	stagedatas[0] = 1; // 스테이지 1에는 맵이 총 1
	stagedatas[1] = 2; // 스테이지 2에는 맵이 총 1
	stagedatas[2] = 1; // 스테이지 3에는 맵이 총 1
	coolTime = TIMECOST;
	Initialize();

	blur = new Sprite;
	blur->isUI = true;
	blur->layer = 10000;
	blur->SetTexture(L"background.png");
	blur->color = D3DCOLOR_RGBA(0, 0, 0, 120);
	blur->position = { screenwidth / 2, screenheight / 2 };
	blur->isactive = false;

	mainButton = new Button;
	mainButton->isUI = true;
	mainButton->layer = 10001;
	mainButton->SetTexture(L"Exit.png");
	mainButton->position = { screenwidth / 2 - 300, screenheight / 2 - 500 };
	mainButton->function = []()
	{
		SceneManager::GetInstance().ChangeScene(L"Main");
	};

	restartButton = new Button;
	restartButton->isUI = true;
	restartButton->layer = 10002;
	restartButton->SetTexture(L"Restart.png");
	restartButton->position = { screenwidth / 2, screenheight / 2 - 500 };
	restartButton->function = []()
	{
		SceneManager::GetInstance().ChangeScene(L"Stage1");
	};

	/*boss = new Boss1;
	boss->player = p;
	boss->position = { screenwidth / 2, screenheight / 2 };
	boss->SetStat(difficulty);*/

	MonsterBulletManager::GetInstance().p = p;
	MonsterBulletManager::GetInstance().Create();
}

void Stage1::Update()
{
	CheatKey();

	if (isPaused)
	{
		SM timeScale = 0.f;
		blur->isactive = true;
		mainButton->isactive = true;
		restartButton->isactive = true;

		D3DXVec2Lerp(&restartButton->position,
			&restartButton->position, 
			&Vec2(screenwidth / 2, screenheight / 2 + 100 ), // 도착 위치
			DXUTGetElapsedTime() * 2);

		D3DXVec2Lerp(&mainButton->position,
			&mainButton->position,
			&Vec2(screenwidth / 2 - 300, screenheight / 2 + 100), // 도착 위치
			DXUTGetElapsedTime() * 2);
	}
	else
	{
		SM timeScale = 1.f;
		blur->isactive = false;
		mainButton->isactive = false;
		restartButton->isactive = false;

		mainButton->position = { screenwidth / 2 - 300, screenheight / 2 - 500 };
		restartButton->position = { screenwidth / 2, screenheight / 2 - 500 };
	}
	

	Camera& cam = Camera::GetInstance();
	D3DXVec2Lerp(&cam.camPos, &cam.camPos, &p->position, SM GetDeltaTime() * 2);

	if (uipack->scoreButton->isactive == false)
		coolTime -= SM GetDeltaTime();

	uipack->Update();

	if (door->CollisionPlayer(p->position)) // 플레이어가 다음 맵으로 넘어갔다
	{
		if (door->currentDoorIndex == mapTXTdata.size())
		{
			RankScene::isCleared = true;
			RankScene::score = p->score;
			SceneManager::GetInstance().ChangeScene(L"End");
		}
		else
		{
			int mapCount = 0;
			// 0일때 1, 1일때 2
			for (int i = 0; i <= currentStage; ++i)
				mapCount += stagedatas[i];
			if (door->currentDoorIndex == mapCount) // 현재 스테이지가 끝나고 다음 스테이지로 넘어가기 직전
			{
				p->hp = p->maxHP;
				p->attackgauge = 0;
				p->hpuigauge = 0;
				// UI띄우는 코드
				// 다음 스테이지로 넘어가기 직전이다.
				// UI 스코어를 계산.
				// 버튼이나 키를 누르면 다음 스테이지로 넘어가야한다.
				uipack->ScoreActive(true);
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(DXUTGetHWND(), &pt);
				if (DXUTIsMouseButtonDown(0))
				{
					if (PtInRect(&uipack->scoreButton->GetRect(), pt))
					{
						uipack->scoreButton->function();
					}
				}

				p->movespeed = 0.f;
				
				if(uipack->isButtonOn == true)
				{
					uipack->isButtonOn = false;
					SetMap(door->currentDoorIndex); // 넘길 때
					Initialize(); // 넘어갔을 때
					++door->currentDoorIndex;
					++currentStage;
					p->movespeed = 300.f;
					uipack->ScoreActive(false);
					coolTime = TIMECOST;
					difficulty = 1;
				}
			}
			else
			{
				SetMap(door->currentDoorIndex); // 넘길 때
				Initialize(); // 넘어갔을 때
				++difficulty;
				++door->currentDoorIndex;
			}
		}
	}

	if (p->isdead == true)
	{
		SceneManager::GetInstance().ChangeScene(L"Fail");
		return;
	}

	if (coolTime < 0)
	{
		SceneManager::GetInstance().ChangeScene(L"Fail");
		return;
	}

	// 버튼 눌리면 들어가기
	if (restartButton->isactive == true)
	{
		// 버튼 두개 검사
		POINT asdfp;
		GetCursorPos(&asdfp);
		ScreenToClient(DXUTGetHWND(), &asdfp);

		if (DXUTIsMouseButtonDown(0))
		{
			if (PtInRect(&restartButton->GetRect(), asdfp))
			{
				restartButton->function();
				return;
			}

			if (PtInRect(&mainButton->GetRect(), asdfp))
			{
				mainButton->function();
				return;
			}
		}

	}

	if (DXUTWasKeyPressed(VK_F4))
	{
		SceneManager::GetInstance().ChangeScene(L"Main");
		return;
	}
}

void Stage1::Exit()
{
	uipack->Delete();
	delete uipack;
	delete p;
	ItemManager::GetInstance().Delete();

	TileMapManager::GetInstance().DeleteBlocks();
	BManager::GetInstance().Delete();
	EManager::GetInstance().Delete();
	MonsterManager::GetInstance().Delete();
	MonsterSpawnerManager::GetInstance().Delete();
	MonsterBulletManager::GetInstance().Delete();

	SoundManager::GetInstance().Stop(L"bgm");

	for (auto iter : chests)
		delete iter;
	chests.clear();

	delete blur;
	delete restartButton;
	delete mainButton;
	delete door;

	isPaused = false;

	mapTXTdata.clear();
}
