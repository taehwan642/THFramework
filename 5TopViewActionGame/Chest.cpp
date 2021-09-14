#include "DXUT.h"
#include "Item.h"
#include "Bullet.h"
#include "Effect.h"
#include "Player.h"
#include "Chest.h"

Chest::Chest()
{
	SetTexture(L"chest (1).png");
	scale = { 0.5,0.5 };
}

void Chest::ItemSpawn()
{
	ItemManager& item = ItemManager::GetInstance();
	item.Spawn(position);
}

void Chest::Collide()
{
	for (auto iter : BManager::GetInstance().bullets)
	{
		if (iter->isactive == false)
			continue;

		RECT r;
		if (IntersectRect(&r, &GetRect(), &iter->GetRect()))
		{
			++hp;
			iter->isactive = false;
			EManager::GetInstance().Spawn(position, E_HIT);
			iter->UpGauge();
			ItemManager::GetInstance().pl->score += 20;
			if (hp > 4)
			{
				ItemSpawn();
				isactive = false;
				return;
			}
			std::wstring tag = L"chest (" + std::to_wstring(hp + 1) + L").png";
			SetTexture(tag);
		}
	}
}

void Chest::Update()
{
	Collide();
}
