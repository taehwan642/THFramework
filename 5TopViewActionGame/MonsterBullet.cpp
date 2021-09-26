#include "DXUT.h"
#include "Player.h"
#include "SceneManager.h"
#include "Effect.h"
#include "TileMapManager.h"
#include "MonsterBullet.h"

MonsterBullet::MonsterBullet()
{
	movespeed = 1000.f;
}

void MonsterBullet::Action()
{
	Vec2 dist = player->position - position;
	float length = D3DXVec2Length(&dist);

	if (length < 40.f)
	{
		player->Damaged(strValue);
		// 방향벡터 구하기
		float dirX = player->position.x - position.x;
		float dirY = player->position.y - position.y;
		Vec2 d = { dirX, dirY };
		// 크기 1로 세팅
		D3DXVec2Normalize(&d, &d);
		// (방향벡터 방향으로) 앞으로 땡겨주기
		Vec2 res =
		{
			d.x * 30,
			d.y * 30
		};

		player->position += res;
		isactive = false;
	}


	if (isCollide)
	{
		EManager::GetInstance().Spawn(position, E_HIT);
		isactive = false;
		position = { -999,-999 };
	}

	if (alivetime < 0)
	{
		isactive = false;
		position = { -999,-999 };
	}

	position += dir * movespeed * SM GetDeltaTime();
	alivetime -= SM GetDeltaTime();
}

void MonsterBulletManager::Create()
{
	for (int i = 0; i < 30; ++i) 
	{
		MonsterBullet* m = new MonsterBullet;
		m->isactive = false;
		m->layer = 3;
		m->player = p;
		mb.push_back(m);
	}
}

void MonsterBulletManager::Spawn(Vec2 pos, Vec2 dir, int damageval, BlockType type)
{
	for (auto iter : mb)
	{
		if (iter->isactive == false)
		{
			iter->alivetime = 3.f;
			iter->isactive = true;
			iter->position = pos;
			D3DXVec2Normalize(&dir, &dir);
			iter->Lookat(-dir, true);
			iter->dir = dir;
			switch (type)
			{
			case MONSTER3:
				iter->SetTexture(L"");
				break;
			case BOSS1:
				iter->SetTexture(L"boss1bullet.png");
				break;
			default:
				break;
			}
			iter->strValue = damageval;
			return;
		}
	}
}

void MonsterBulletManager::Delete()
{
	for (auto iter : mb)
	{
		delete iter;
	}
	mb.clear();
}
