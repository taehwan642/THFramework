#include "DXUT.h"
#include "Effect.h"

void EManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Effect* e = new Effect;
		e->isactive = false;
		effects.push_back(e);
	}
}

void EManager::Spawn(Vec2 pos, EffectTag tag)
{
	for (auto iter : effects)
	{
		if (iter->isactive == false)
		{
			iter->position = pos;
			iter->tag = tag;

			iter->isactive = true;
			return;
		}
	}
}

void EManager::Delete()
{
	for (auto iter : effects)
		delete iter;
	effects.clear();
}

Effect::Effect()
{
	CreateAnimation(L"boom", 8, 0.05f);
	CreateAnimation(L"dust", 4, 0.1f);
	CreateAnimation(L"heal", 5, 0.3f);
	CreateAnimation(L"hit", 3, 0.05f);
	PlayAnimation(L"hit");
	scale = { 0.5,0.5 };
}

void Effect::Update()
{
	bool isEnd = false;
	switch (tag)
	{
	case E_BOMB:
		isEnd = PlayAnimation(L"boom");
		break;
	case E_HIT:
		isEnd = PlayAnimation(L"hit");
		break;
	case E_HEAL:
		isEnd = PlayAnimation(L"heal");
		break;
	case E_DUST:
		isEnd = PlayAnimation(L"dust");
		break;
	default:
		break;
	}

	if (isEnd == true)
		isactive = false;
}
