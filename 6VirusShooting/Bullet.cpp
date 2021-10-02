#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet()
{
	CreateAnimation(L"Sprites/bullet/machinegunBullet/bullet", 1, 0.1f);
	CreateAnimation(L"Sprites/bullet/navalgunBullet/bullet", 1, 0.1f);
	CreateAnimation(L"Sprites/bullet/Torpedo/torpedo", 30, 0.1f);
	CreateAnimation(L"Sprites/bullet/PlayerMissile/missile", 30, 0.1f);
	CreateAnimation(L"Sprites/bullet/PlayerMissile/missile", 30, 0.1f);
	CreateAnimation(L"Sprites/bullet/EnemyMissile/missile", 30, 0.1f);
}

void Bullet::Move()
{
	if (type == B_MISSILE || type == B_TORPEDO)
	{
		dir = *target - position;
		D3DXVec2Normalize(&dir, &dir);
		position += dir * Time::dt * movespeed;
		Lookat(-dir, true);
	}
	else
	{
		position += dir * Time::dt * movespeed;
	}

	if (position.x > screenwidth + 100)
		isactive = false;
	if (position.x < -100)
		isactive = false;
	if (position.y > screenheight + 100)
		isactive = false;
	if (position.y < -100)
		isactive = false;
}

void Bullet::Update()
{
	Move();
	switch (type)
	{
	case B_MISSILE:
		PlayAnimation(L"Sprites/bullet/PlayerMissile/missile");
		break;
	case B_TORPEDO:
		PlayAnimation(L"Sprites/bullet/Torpedo/torpedo");
		break;
	case B_MACHINEGUNBULLET:
		PlayAnimation(L"Sprites/bullet/machinegunBullet/bullet");
		break;
	case B_NAVALGUNBULLET:
		PlayAnimation(L"Sprites/bullet/navalgunBullet/bullet");
		break;
	case B_ENEMYTORPEDO:
		PlayAnimation(L"Sprites/bullet/Torpedo/torpedo");
		break;
	case B_ENEMYMISSILE:
		PlayAnimation(L"Sprites/bullet/EnemyMissile/missile");
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

void BulletManager::Spawn(Vec2 pos, Vec2 dir, BulletType type, Vec2* target, int damage)
{
	for (auto iter : b)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			D3DXVec2Normalize(&dir, &dir);
			iter->dir = dir;
			iter->target = target;
			iter->Lookat(-dir, true);
			iter->type = type;
			iter->damage = damage;
			iter->isactive = true;
			if (type == B_TORPEDO || type == B_MISSILE)
				iter->movespeed = 600;
			else
				iter->movespeed = 1000;

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
