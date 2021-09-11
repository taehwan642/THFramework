#include "DXUT.h"
#include "Player.h"
#include "Effect.h"
#include "Item.h"

void Item::Effect(Player* p)
{
	switch (type)
	{
	case I_HEAL:
		p->Heal(1);
		isactive = false;
		break;
	case I_ATTACKUP:
		p->attackupTick = 3.0f;
		isactive = false;
		break;
	case I_HPUIUP:
		p->HpUIUp(1);
		isactive = false;
		break;
	default:
		break;
	}
}

void Item::Update()
{
	if (type == I_BOMB)
	{
		tick -= DXUTGetElapsedTime();
		if (tick < 0)
		{
			// 빵!
			EManager::GetInstance().Spawn(position, E_BOMB);
			// for(적)
			// 플레이어
			
			// 원 반경
			Vec2 dist = pl->position - position;
			float length = D3DXVec2Length(&dist);
			// sqrt(dist.x^2 + dist.y^2) // 피타고라스
			if (length < radius)
			{
				// 안에 들어왔네. 빵빵!!
				pl->Damaged(1);
			}
			isactive = false;
		}
	}
}

void ItemManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Item* it = new Item;
		it->isactive = false;
		it->pl = pl; // 플레이어 할당 부분
		it->scale = { 0.5,0.5 };
		items.push_back(it);
	}
}

void ItemManager::Spawn(Vec2 pos)
{
	// 폭탄 터지기 결정
	for (auto iter : items)
	{
		if (false == iter->isactive)
		{
			iter->isactive = true;
			int r = rand() % I_END;
			iter->type = (ItemType)r;
			iter->tick = 2.f;
			iter->position = pos; // 상자 위치

			switch (iter->type)
			{
			case I_HEAL:
				iter->SetTexture(L"Hpitem.png");
				break;
			case I_ATTACKUP:
				iter->SetTexture(L"Power.png");
				break;
			case I_HPUIUP:
				iter->SetTexture(L"hpui (5).png");
				break;
			case I_BOMB:
				iter->SetTexture(L"Bomb.png");
				break;
			default:
				break;
			}
			return;
		}
	}
}

void ItemManager::Delete()
{
	for (auto iter : items)
	{
		delete iter;
	}
	items.clear();
}
