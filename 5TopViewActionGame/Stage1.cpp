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
#include "Stage1.h"

void Stage1::Initialize()
{
	for (auto iter : chests)
		delete iter;
	chests.clear();

	for (auto iter : MonsterManager::GetInstance().monsters)
	{
		if(iter != nullptr)
			iter->isactive = false;
	}

	for (auto iter : MonsterSpawnerManager::GetInstance().spn)
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
	// �÷��̾�
	TileMapManager& tm = TileMapManager::GetInstance();

	MapTXTData data;
	data.blockTXT = "mapblock.txt";
	data.objTXT = "mapobj.txt";
	mapTXTdata.push_back(data);

	data.blockTXT = "mapblock2.txt";
	data.objTXT = "mapobj2.txt";
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
	stagedatas[0] = 1; // �������� 1���� ���� �� 1
	stagedatas[1] = 1; // �������� 2���� ���� �� 1
	stagedatas[2] = 1; // �������� 3���� ���� �� 1
	coolTime = TIMECOST;
	Initialize();
}

void Stage1::Update()
{
	if(DXUTWasKeyPressed('B'))
		ItemManager::GetInstance().Spawn({ screenwidth / 2, screenheight / 2 });

	Camera& cam = Camera::GetInstance();
	D3DXVec2Lerp(&cam.camPos, &cam.camPos, &p->position, DXUTGetElapsedTime() * 2);

	if (uipack->scoreButton->isactive == false)
		coolTime -= DXUTGetElapsedTime();

	uipack->Update();

	if (door->CollisionPlayer(p->position)) // �÷��̾ ���� ������ �Ѿ��
	{
		if (door->currentDoorIndex == mapTXTdata.size())
		{
			SceneManager::GetInstance().ChangeScene(L"End");
			RankScene::isCleared = true;
		}
		else
		{
			int mapCount = 0;
			// 0�϶� 1, 1�϶� 2
			for (int i = 0; i <= currentStage; ++i)
				mapCount += stagedatas[i];
			if (door->currentDoorIndex == mapCount) // ���� ���������� ������ ���� ���������� �Ѿ�� ����
			{
				// UI���� �ڵ�
				// ���� ���������� �Ѿ�� �����̴�.
				// UI ���ھ ���.
				// ��ư�̳� Ű�� ������ ���� ���������� �Ѿ���Ѵ�.
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
					SetMap(door->currentDoorIndex); // �ѱ� ��
					Initialize(); // �Ѿ�� ��
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
				SetMap(door->currentDoorIndex); // �ѱ� ��
				Initialize(); // �Ѿ�� ��
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
}

void Stage1::Exit()
{
	uipack->Delete();
	delete p;
	ItemManager::GetInstance().Delete();

	TileMapManager::GetInstance().DeleteBlocks();
	BManager::GetInstance().Delete();
	EManager::GetInstance().Delete();
	MonsterManager::GetInstance().Delete();
	MonsterSpawnerManager::GetInstance().Delete();

	SoundManager::GetInstance().Stop(L"bgm");

	for (auto iter : chests)
		delete iter;
	chests.clear();
}
