#include "DXUT.h"
#include "Monster.h"
#include "TileMapManager.h"
#include "MonsterSpawner.h"

MonsterSpawner::MonsterSpawner()
{
	SetTexture(L"MonsterSpawner.png");
	TileMapManager& tm = TileMapManager::GetInstance();
	scale = { tm.blockScale, tm.blockScale };
	layer = 30;
}

MonsterSpawner::~MonsterSpawner()
{
}

void MonsterSpawner::SetMonsterType(std::vector<int> type)
{
	monsterType = type;
}

void MonsterSpawner::Update()
{
	// 일정 쿨타임이 지나면
	// 스폰
	// 근데 누굴 스폰시킬지는 난수로 정하기.
	tick += DXUTGetElapsedTime();
	if (tick > cooltime)
	{
		if (monsterSpawnValue > 0)
		{
			int type = rand() % monsterType.size();
			MonsterManager::GetInstance().Spawn((BlockType)monsterType[type], position, difficulty);
			tick = 0.f;
			--monsterSpawnValue;
		}
	}
}

void MonsterSpawnerManager::Create()
{
	for (int i = 0; i < 10; ++i)
	{
		MonsterSpawner* sp = new MonsterSpawner;
		sp->isactive = false;
		spn.push_back(sp);
	}
}

void MonsterSpawnerManager::Spawn(int spawnValue, std::vector<int> types, Vec2 position)
{
	for (auto iter : spn)
	{
		if (iter->isactive == false)
		{
			iter->monsterSpawnValue = spawnValue;
			iter->position = position;
			iter->SetMonsterType(types);
			iter->isactive = true;
			return;
		}
	}
}

void MonsterSpawnerManager::Delete()
{
	for (auto iter : spn)
	{
		delete iter;
	}
	spn.clear();
}
