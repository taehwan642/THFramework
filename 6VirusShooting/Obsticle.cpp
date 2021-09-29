#include "DXUT.h"
#include "Player.h"
#include "Bullet.h"
#include "Item.h"
#include "Obsticle.h"

Obsticle::Obsticle()
{
	CreateAnimation(L"Sprites/bullet/mine/mine", 30, 0.05f);
	CreateAnimation(L"Sprites/bullet/Garbage/type1/trash", 30, 0.05f);
	CreateAnimation(L"Sprites/bullet/Garbage/type2/trash", 30, 0.05f);
}

void Obsticle::CollideWithBullet()
{
	for (auto iter : BulletManager::GetInstance().b)
	{
		if (iter->isactive == false)
			continue;

		Vec2 dist = iter->position - position;
		float length = D3DXVec2Length(&dist);
		if (length < 70.f)
		{
			--hp;
			if (hp <= 0)
			{
				int r = rand() % I_END;
				ItemManager::GetInstance().Spawn(position, (ItemType)r);
				isactive = false;
			}
			iter->isactive = false;
		}
	}
}

void Obsticle::CollideWithPlayer()
{
	Vec2 dist = player->position - position;
	float length = D3DXVec2Length(&dist);
	if (length < 70.f)
	{
		player->Damaged(1);
	}
}

void Obsticle::Update()
{
	CollideWithPlayer(); CollideWithBullet();
	switch (type)
	{
	case O_MINEOBS:
		PlayAnimation(L"Sprites/bullet/mine/mine");
		break;
	case O_TRASHOBS:
	{
		std::wstring route = L"Sprites/bullet/Garbage/type";
		route += std::to_wstring(trashtype + 1);
		route += L"/trash";
		PlayAnimation(route);
		break;
	}
	default:
		break;
	}

	position.x -= movespeed * Time::dt;
}

void ObsticleManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{	
		Obsticle* ob = new Obsticle;
		ob->player = player;
		ob->isactive = false;
		o.push_back(ob);
	}
}

void ObsticleManager::Spawn(Vec2 pos, ObsticleType type)
{
	for (auto iter : o)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			iter->type = type;
			iter->hp = 5;
			iter->isactive = true;
			if (type == O_TRASHOBS)
				iter->trashtype = rand() % 2;
			return;
		}
	}
}

void ObsticleManager::Delete()
{
	for (auto iter : o)
	{
		delete iter;
	}
	o.clear();
}
