#include "DXUT.h"
#include "Player.h"
#include "Effect.h"
#include "Bullet.h"

void BManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Bullet* b = new Bullet;
		b->player = player;
		b->isactive = false;
		b->layer = 3;
		bullets.push_back(b);
	}
}

void BManager::Spawn(Vec2 pos, Vec2 mousepos, int damage, int spawntype, bool isWeak)
{
	for (auto iter : bullets)
	{
		if (iter->isactive == false)
		{
			if (spawntype == 0)
			{
				Vec2 d = mousepos - pos; // 방향벡터
				D3DXVec2Normalize(&iter->dir, &d);
				// 데미지
				iter->strValue = damage;
				iter->isactive = true;
				iter->position = pos + iter->dir * 5; // 총구쪽으로 조금 가깝게 당겨주기
				iter->alivetime = 3.f;
				iter->isWeak = isWeak;
				iter->Lookat(mousepos);
			}
			else
			{
				D3DXVec2Normalize(&iter->dir, &mousepos);
				// 데미지
				iter->strValue = damage;
				iter->isactive = true;
				iter->position = pos + iter->dir * 5; // 총구쪽으로 조금 가깝게 당겨주기
				iter->alivetime = 3.f;
				iter->isWeak = isWeak;
				iter->Lookat(-iter->dir, true);
			}
			// dir 진행방향
			
			return;
		}
	}
}

void BManager::Delete()
{
	for (auto iter : bullets)
	{
		delete iter;
	}
	bullets.clear();
}

Bullet::Bullet()
{
	movespeed = 1000.f;
	strValue = 1;
	SetTexture(L"bullet.png");
}

void Bullet::UpGauge()
{
	if(isWeak == true)
		++player->attackgauge;
}

void Bullet::Action()
{
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

	position += dir * movespeed * DXUTGetElapsedTime();
	alivetime -= DXUTGetElapsedTime();
}
