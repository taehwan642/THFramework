#include "DXUT.h"
#include "Bullet.h"

void BManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Bullet* b = new Bullet;
		b->isactive = false;
		b->layer = 3;
		bullets.push_back(b);
	}
}

void BManager::Spawn(Vec2 pos, Vec2 mousepos, int damage)
{
	for (auto iter : bullets)
	{
		if (iter->isactive == false)
		{
			// dir 진행방향
			Vec2 d = mousepos - pos; // 방향벡터
			D3DXVec2Normalize(&iter->dir, &d);
			// 데미지
			iter->damage = damage;
			iter->isactive = true;
			iter->position = pos + iter->dir * 5; // 총구쪽으로 조금 가깝게 당겨주기
			iter->alivetime = 3.f;
			iter->Lookat(mousepos);

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
	SetTexture(L"bullet.png");
}

void Bullet::Update()
{
	position += dir * speed * DXUTGetElapsedTime();
	alivetime -= DXUTGetElapsedTime();
	if (alivetime < 0)
	{
		isactive = false;
	}
}
