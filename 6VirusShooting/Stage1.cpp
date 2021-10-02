#include "DXUT.h"
#include "UIPack.h"
#include "Effect.h"
#include "Player.h"
#include "Bullet.h"
#include "Obsticle.h"
#include "Item.h"
#include "MessageBoy.h"
#include "Monster.h"
#include "Stage1.h"

void Stage1::Init()
{
	pack = new UIPack;
	pack->Init();

	player = new Player;
	pack->player = player;

	EffectManager::GetInstance().Create();
	BulletManager::GetInstance().Create();
	ObsticleManager::GetInstance().player = player;
	ObsticleManager::GetInstance().Create();
	ItemManager::GetInstance().player = player;
	ItemManager::GetInstance().Create();

	MessageBoy::GetInstance().Create();
	MonsterManager::GetInstance().Create();
	// float x = -100;
	// y = 0 ~ 720 (40)
	

}

void Stage1::Update()
{
	monsterSpawnTime -= Time::dt;
	if (monsterSpawnTime < 0)
	{
		Vec2 pos;
		pos.x = screenwidth + 100;
		pos.y = (rand() % 640) + 40;
		MonsterManager::GetInstance().Spawn(pos, M_SEAMONSTER, true);
		monsterSpawnTime = 9999.5f;
	}


	if (DXUTWasKeyPressed('P'))
	{
		int r = rand() % O_END;
		ObsticleManager::GetInstance().Spawn(MIDDLE, O_MINEOBS);//(ObsticleType)r);
	}
	MessageBoy::GetInstance().Update();
	pack->Update();
}

void Stage1::Exit()
{
	pack->Delete();
	EffectManager::GetInstance().Delete();
	BulletManager::GetInstance().Delete();
	ObsticleManager::GetInstance().Delete();
	ItemManager::GetInstance().Delete();
	delete pack;
	delete player;
	MessageBoy::GetInstance().Delete();
	MonsterManager::GetInstance().Delete();
}
