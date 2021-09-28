#include "DXUT.h"
#include "Effect.h"

Effect::Effect()
{
	CreateAnimation(L"Sprites/effect/AirSupprt/airsupport", 31, 0.05f);
	CreateAnimation(L"Sprites/effect/explo/explosion", 23, 0.05f);
}

void Effect::Update()
{
	bool isEnd = false;
	switch (type)
	{
	case E_AIRSUPPORT:
		isEnd = PlayAnimation(L"Sprites/effect/AirSupprt/airsupport");
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

void EffectManager::Spawn(Vec2 pos, EffectType type)
{
	for (auto iter : eff)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			iter->type = type;
			iter->isactive = true;
			return;
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
