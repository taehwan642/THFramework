#include "DXUT.h"
#include "Items.h"

void Items::Heal(VIM* vim)
{
	if (vim->HP < 5)
		++vim->HP;
	else
	{
		// 스코어 올림.
		++vim->vimscore;
	}
}

void Items::Barrier(VIM* vim)
{
	vim->barriervalue = 1;
}

void Items::Immune(VIM* vim)
{
	vim->immunetime = 15.f;
}

void Items::Speed(VIM* vim)
{
	vim->movementspeed -= 0.01f;
}

Items::Items()
{
	layer = 2;
	SetTexture(L"Item.png");
	scale = { 0.07f,0.07f };
}

Items::~Items()
{
}

void Items::GetItem(VIM* vim)
{
	switch (tag)
	{
	case SPEED:
		Speed(vim);
		break;
	case BARRIER:
		Barrier(vim);
		break;
	case IMMUNE:
		Immune(vim);
		break;
	case HEAL:
		Heal(vim);
		break;
	case RANDOM:
	{
		int r = rand() % RANDOM;
		if (r == SPEED)
		{
			Speed(vim);
		}
		else if (r == BARRIER)
		{
			Barrier(vim);
		}
		else if (r == IMMUNE)
		{
			Immune(vim);
		}
		else if (r == HEAL)// r == HEAL
		{
			Heal(vim);
		}
		break;
	}
	default:
		break;
	}
}

void Items::Update()
{

}

void ItemManager::CreateItem()
{
	for (int i = 0; i < 10; ++i)
	{
		Items* it = new Items();
		it->isactive = false;
		items.emplace_back(it);
	}
}

void ItemManager::SpawnItem(Vec2 _position, int _X, int _Y, ITEMTAG _tag)
{
	for (int i = 0; i < items.size(); ++i)
	{
		if (items[i]->isactive == false)
		{
			items[i]->isactive = true;
			items[i]->position = _position;
			items[i]->tag = _tag;
			items[i]->ItemIndexX = _X;
			items[i]->ItemIndexY = _Y;

			switch (_tag)
			{
			case SPEED:
				items[i]->SetTexture(L"blueItem.png");
				break;
			case BARRIER:
				items[i]->SetTexture(L"yellowItem.png");
				break;
			case IMMUNE:
				items[i]->SetTexture(L"mintItem.png");
				break;
			case HEAL:
				items[i]->SetTexture(L"greenItem.png");
				break;
			case RANDOM:
				items[i]->SetTexture(L"orangeItem.png");
				break;
			default:
				break;
			}
			return;
		}
	}
}

void ItemManager::CheckItem(int _X, int _Y, VIM* vim)
{
	for (int i = 0; i < items.size(); ++i)
	{
		if (items[i]->isactive == true)
		{
			if (items[i]->ItemIndexX == _X &&
				items[i]->ItemIndexY == _Y)
			{
				items[i]->GetItem(vim);
				items[i]->isactive = false;
			}
		}
	}
}

void ItemManager::DeleteItem()
{
	for (int i = 0; i < items.size(); ++i)
	{
		delete items[i];
	}
	items.clear();
}
