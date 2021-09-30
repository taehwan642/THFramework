#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet()
{
	CreateAnimation(L"Sprites/bullet/machinegunBullet/bullet", 1, 0.1f);
	CreateAnimation(L"Sprites/bullet/navalgunBullet/bullet", 1, 0.1f);
}

void Bullet::Move()
{
	position += dir * Time::dt * movespeed;
	if (position.x > screenwidth + 100)
		isactive = false;
}

void Bullet::Update()
{
	Move();
	switch (type)
	{
	case B_MACHINEGUNBULLET:
		PlayAnimation(L"Sprites/bullet/machinegunBullet/bullet");
		break;
	case B_NAVALGUNBULLET:
		PlayAnimation(L"Sprites/bullet/navalgunBullet/bullet");
		break;
	default:
		break;
	}
}

void BulletManager::Create()
{
	for (int i = 0; i < 50; ++i)
	{
		Bullet* bu = new Bullet;
		bu->isactive = false;
		b.push_back(bu);
	}
}

void BulletManager::Spawn(Vec2 pos, Vec2 dir, BulletType type)
{
	for (auto iter : b)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			D3DXVec2Normalize(&dir, &dir);
			iter->dir = dir;
			iter->Lookat(-dir, true);
			iter->type = type;
			iter->isactive = true;
			return;
		}
	}
}

void BulletManager::Delete()
{
	for (auto iter : b)
	{
		delete iter;
	}
	b.clear();
}
