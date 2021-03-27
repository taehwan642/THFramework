#include "DXUT.h"
#include "Effects.h"

Effects::Effects()
{
	layer = 5;
	SetTexture(L"flash (1).png");
	scale = { 0.3,0.3 };
}

Effects::~Effects()
{

}

void Effects::Update()
{
	switch (tag)
	{
	case EFLASH:
		if (Animation(L"flash", 0.1f, 4))
		{
			std::cout << "¿ì¿Õ¿ì¿Õ" << std::endl;
			isactive = false;
		}
		break;
	default:
		break;
	}
}

void EffectManager::CreateEffect()
{
	for (int i = 0; i < 30; ++i)
	{
		Effects* e = new Effects();
		e->isactive = false;
		effects.emplace_back(e);
	}
}

void EffectManager::SpawnEffect(Vec2 _position, EFFECTTAG _tag)
{
	for (int i = 0; i < effects.size(); ++i)
	{
		if (effects[i]->isactive == false)
		{
			effects[i]->position = _position;
			effects[i]->isactive = true;
			effects[i]->tag = _tag;

			switch (_tag)
			{
			case EFLASH:
				effects[i]->SetTexture(L"flash (1).png");
				break;
			default:
				break;
			}
			return;
		}
	}
}

void EffectManager::DeleteEffect()
{
	for (int i = 0; i < effects.size(); ++i)
	{
		delete effects[i];
	}
	effects.clear();
}
