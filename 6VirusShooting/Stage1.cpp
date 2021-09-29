#include "DXUT.h"
#include "UIPack.h"
#include "Effect.h"
#include "Player.h"
#include "Bullet.h"
#include "Obsticle.h"
#include "Item.h"
#include "Stage1.h"

void Stage1::Init()
{
	pack = new UIPack;
	pack->Init();

	player = new Player;

	EffectManager::GetInstance().Create();
	BulletManager::GetInstance().Create();
	ObsticleManager::GetInstance().player = player;
	ObsticleManager::GetInstance().Create();
	ItemManager::GetInstance().player = player;
	ItemManager::GetInstance().Create();
}

void Stage1::Update()
{
	if (DXUTWasKeyPressed('P'))
	{
		int r = rand() % O_END;
		ObsticleManager::GetInstance().Spawn(MIDDLE, (ObsticleType)r);
	}

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
}
