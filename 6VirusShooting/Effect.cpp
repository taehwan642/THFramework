#include "DXUT.h"
#include "Monster.h"
#include "Effect.h"

Effect::Effect()
{
	CreateAnimation(L"Sprites/effect/AirSupprt/airsupport", 31, 0.05f);
	CreateAnimation(L"Sprites/effect/explo/explosion", 23, 0.05f);
	layer = 100;
	RenderManager::GetInstance().Sort();
}

void Effect::Update()
{
	bool isEnd = false;
	switch (type)
	{
	case E_AIRSUPPORT:
		isEnd = PlayAnimation(L"Sprites/effect/AirSupprt/airsupport");
		if (currentFrame == 11)
		{
			for (auto iter : MonsterManager::GetInstance().m)
			{
				if (iter->isactive == false)
					continue;
				if (iter->isdead == true)
					continue;

				iter->Damaged(100);
			}
		}
		break;
	case E_EXPLOSION:
		isEnd = PlayAnimation(L"Sprites/effect/explo/explosion");
		break;
	default:
		break;
	}
	if (isEnd == true)
		isactive = false;
}

void EffectManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Effect* e = new Effect;
		e->isactive = false;
		eff.push_back(e);
	}
}

Effect* EffectManager::Spawn(Vec2 pos, EffectType type)
{
	for (auto iter : eff)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			iter->type = type;
			iter->isactive = true;
			if (type == E_EXPLOSION)
				iter->scale = { 3,3 };
			else
				iter->scale = { 1,1 };
			return iter;
		}
	}
}

void EffectManager::Delete()
{
	for (auto iter : eff)
	{
		delete iter;
	}
	eff.clear();
}
