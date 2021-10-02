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
	radius = new Sprite;
	radius->isactive = false;
	radius->SetTexture(L"Sprites/bullet/RedLight/00.png");
	radius->scale = { 3.5f, 3.5f };
	radius->layer = -1;
	RenderManager::GetInstance().Sort();
	position = { -9999, -9999 };
	radius->position = { -9999, -9999 };
}

Obsticle::~Obsticle()
{
	delete radius;
}

void Obsticle::Mine()
{
	player->Damaged(3);
	player->speedbuffTime = 1.f;
	player->speedbuffValue = -300 / 2.f;
}

void Obsticle::Trash()
{
	player->speedbuffTime = 1.f;
	player->speedbuffValue = -100.f;
}

void Obsticle::CollideWithBullet()
{
	for (auto iter : BulletManager::GetInstance().b)
	{
		if (iter->isactive == false)
			continue;

		if (iter->type == B_ENEMYMISSILE || iter->type == B_ENEMYTORPEDO)
			continue;

		Vec2 dist = iter->position - position;
		float length = D3DXVec2Length(&dist);
		if (length < 70.f)
		{
			hp -= iter->damage;
			if (hp <= 0)
			{
				int r = rand() % I_END;
				ItemManager::GetInstance().Spawn(position, (ItemType)r);
				isactive = false;
				radius->isactive = false;
				position = { -9999, -9999 };
				radius->position = { -9999, -9999 };
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
		switch (type)
		{
		case O_MINEOBS:
			Mine();
			break;
		case O_TRASHOBS:
			Trash();
			break;
		default:
			break;
		}
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
	radius->position = position;
	position.x -= movespeed * Time::dt;

	if (position.x > screenwidth + 100 ||
		position.x < -100 ||
		position.y > screenheight + 100 ||
		position.y < -100)
	{
		isactive = false;
		radius->isactive = false;
	}
	
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
			else
			{
				iter->radius->isactive = true;
			}
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
