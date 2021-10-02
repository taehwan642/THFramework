#include "DXUT.h"
#include "Bullet.h"
#include "Obsticle.h"
#include "Item.h"
#include "Effect.h"
#include "Monster.h"


void Monster::Boss1Pattern1()
{
	for (int r = -30; r <= 30; r += 15)
	{
		float x = cos(D3DXToRadian(r));
		float y = sin(D3DXToRadian(r));

		BulletManager::GetInstance().Spawn(position, -Vec2(x, y), B_ENEMYMISSILE, nullptr, 1);
	}
}

void Monster::Boss1Pattern2()
{
	ObsticleManager::GetInstance().Spawn(position, O_MINEOBS);
	ObsticleManager::GetInstance().Spawn(Vec2(position.x, position.y - 30), O_MINEOBS);
	ObsticleManager::GetInstance().Spawn(Vec2(position.x, position.y + 30), O_MINEOBS);
}



Monster::Monster()
{
	// Sprites\enemy\type1\move\18
	CreateAnimation(L"Sprites/enemy/type1/move/18/move", 30, 0.05f);
	CreateAnimation(L"Sprites/enemy/type1/sink/18/sink", 28, 0.05f);
	CreateAnimation(L"Sprites/enemy/type2/move/18/move", 30, 0.05f);

	//CreateAnimation(L"Sprites/enemy/typeboss1/enter/in", 52, 0.1f);
	CreateAnimation(L"Sprites/enemy/typeboss1/move/move", 30, 0.05f);
	movespeed = 300.f;
	position = { -9999, -9999 };
}

void Monster::Dead()
{
	int r = rand() % I_END;
	ItemManager::GetInstance().Spawn(position, (ItemType)r);
	EffectManager::GetInstance().Spawn(position, E_EXPLOSION);
}

void Monster::CollideBullet()
{
	for (auto iter : BulletManager::GetInstance().b)
	{
		if (iter->isactive == false)
			continue;

		if (iter->type == B_ENEMYMISSILE || iter->type == B_ENEMYTORPEDO)
			continue;

		if (type == M_SKYMONSTER && iter->type == B_TORPEDO)
			continue;
		if (type == M_SEAMONSTER && iter->type == B_MISSILE)
			continue;


		Vec2 dist = iter->position - position;
		float length = D3DXVec2Length(&dist);
		if (length < 70.f)
		{
			Damaged(iter->damage);
			iter->isactive = false;
		}
	}
}

void Monster::Action()
{
	if (isdead)
	{
		switch (type)
		{
		case M_SEAMONSTER:
			if (isBoss)
			{
				position.x += Time::dt * movespeed * 1.5f;
				if (position.x > screenwidth + 100)
				{
					position = { -9999, -9999 };
					isactive = false;
				}
			}
			else
			{
				if (PlayAnimation(L"Sprites/enemy/type1/sink/18/sink"))
				{
					position = { -9999, -9999 };
					isactive = false;
				}
			}
			break;
		case M_SKYMONSTER:
			position.x += Time::dt * movespeed * 1.5f;
			if (position.x > screenwidth + 100)
			{
				position = { -9999, -9999 };
				isactive = false;
			}
			break;
		default:
			break;
		}
		
	}
	else
	{
		switch (type)
		{
		case M_SEAMONSTER:
			if (isBoss)
				PlayAnimation(L"Sprites/enemy/typeboss1/move/move");
			else
				PlayAnimation(L"Sprites/enemy/type1/move/18/move");
			break;
		case M_SKYMONSTER:
			PlayAnimation(L"Sprites/enemy/type2/move/18/move");
			break;
		default:
			break;
		}

		CollideBullet();
		skilltime -= Time::dt;

		if (attackspeed < 0)
		{
			switch (type)
			{
			case M_SEAMONSTER:
			{
				if (isBoss == false)
					BulletManager::GetInstance().Spawn(position, Vec2(-1, 0), B_ENEMYTORPEDO, nullptr, 1);
				else
				{
					int r = rand() % 2;
					if (r == 0)
						Boss1Pattern1();
					else
						Boss1Pattern2();
				}
			}
				break;
			case M_SKYMONSTER:
			{
				for (int r = -15; r <= 15; r += 15)
				{
					float x = cos(D3DXToRadian(r));
					float y = sin(D3DXToRadian(r));

					BulletManager::GetInstance().Spawn(position, -Vec2(x, y), B_ENEMYMISSILE, nullptr, 1);
				}
				break;
			}
			default:
				break;
			}
			attackspeed = 1.f;
		}

		if (type == M_SEAMONSTER && isBoss == false)
		{
			if (skilltime < 0)
			{
				int ran = rand() % 1;
				if (ran == 0)
				{
					ObsticleManager::GetInstance().Spawn(position, O_MINEOBS);
				}
				skilltime = 3.f;
			}
		}
		
		position.x -= Time::dt * movespeed;

		if (position.x > screenwidth + 100)
			isactive = false;
		if (position.x < -100)
			isactive = false;
		if (position.y > screenheight + 100)
			isactive = false;
		if (position.y < -100)
			isactive = false;
	}
}

void MonsterManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Monster* s = new Monster;
		s->isactive = false;
		m.push_back(s);
	}
}

void MonsterManager::Spawn(Vec2 pos, MonsterTag type, bool isBoss)
{
	for (auto& iter : m)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			iter->type = type;
			iter->isactive = true;
			iter->isdead = false;
			iter->hp = iter->maxHP;
			if (isBoss)
				iter->scale = { 0.3,0.3 };
			else
				iter->scale = { 1,1 };
			iter->isBoss = isBoss;
			return;
		}
	}
}

void MonsterManager::Delete()
{
	for (auto iter : m)
	{
		delete iter;
	}
	m.clear();
}
