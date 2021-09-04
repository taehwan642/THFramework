#include "DXUT.h"
#include "Effect.h"

Effect::Effect()
{
	layer = 3;
	CreateAnimation(L"dust", 4, 0.1f);
	CreateAnimation(L"hit", 3, 0.1f);
	CreateAnimation(L"heal", 5, 0.1f);
	PlayAnimation(L"dust");
}

void Effect::Update()
{
	bool isAnimationEnd = false;
	switch (effect)
	{
	case Effects::DUST:
		isAnimationEnd = PlayAnimation(L"dust");
		break;
	case Effects::HEAL:
		isAnimationEnd = PlayAnimation(L"heal");
		break;
	case Effects::HIT:
		isAnimationEnd = PlayAnimation(L"hit");
		break;
	default:
		break;
	}
	if (true == isAnimationEnd)
		isactive = false;
}

void EffectManager::CreateEffect()
{
	for (int i = 0; i < 30; ++i)
	{
		Effect* eff = new Effect;
		eff->isactive = false;
		effects.push_back(eff);
	}
}

void EffectManager::SpawnEffect(Effects effect, const Vec2& position)
{
	for (auto& iter : effects)
	{
		if (false == iter->isactive)
		{
			iter->effect = effect;
			iter->position = position;
			iter->isactive = true;
			return;
		}
	}
}

void EffectManager::DeleteEffect()
{
	for (auto& iter : effects)
	{
		delete iter;
	}
	effects.clear();
}
