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
			// ��!
			EManager::GetInstance().Spawn(position, E_BOMB);
			// for(��)
			// �÷��̾�
			
			// �� �ݰ�
			Vec2 dist = pl->position - position;
			float length = D3DXVec2Length(&dist);
			// sqrt(dist.x^2 + dist.y^2) // ��Ÿ���
			if (length < radius)
			{
				// �ȿ� ���Գ�. ����!!
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
		it->pl = pl; // �÷��̾� �Ҵ� �κ�
		it->scale = { 0.5,0.5 };
		items.push_back(it);
	}
}

void ItemManager::Spawn(Vec2 pos)
{
	// ��ź ������ ����
	for (auto iter : items)
	{
		if (false == iter->isactive)
		{
			iter->isactive = true;
			int r = rand() % I_END;
			iter->type = (ItemType)r;
			iter->tick = 2.f;
			iter->position = pos; // ���� ��ġ

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
