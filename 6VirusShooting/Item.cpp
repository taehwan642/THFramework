#include "DXUT.h"
#include "Player.h"
#include "Item.h"

void Item::Booster()
{
	player->speedbuffTime = 2.f;
}

void Item::Toolbox()
{
	++player->hp;
	if (player->maxHP <= player->hp)
	{
		player->hp = player->maxHP;
	}
}

void Item::Eventbox()
{
	player->invincibleTime = 2.f;
}

void Item::CollideWithPlayer()
{
	Vec2 dist = player->position - position;
	float length = D3DXVec2Length(&dist);
	std::cout << length << std::endl;
	if (length < 100.f)
	{
		switch (type)
		{
		case I_MACHINEGUNBULLET:
			break;
		case I_TORPEDO:
			break;
		case I_MISSILE:
			break;
		case I_BOOSTER:
			Booster();
			break;
		case I_TOOLBOX:
			Toolbox();
			break;
		case I_EVENTBOX:
			Eventbox();
			break;
		default:
			break;
		}

		isactive = false;
	}
}

Item::Item()
{
	CreateAnimation(L"Sprites/Item/toolbox/toolbox", 30, 0.05f);
	CreateAnimation(L"Sprites/Item/eventbox/eventbox", 30, 0.05f);
	CreateAnimation(L"Sprites/Item/Boost/boost", 1, 1);
}

void Item::Update()
{
	CollideWithPlayer();
	switch (type)
	{
	case I_MACHINEGUNBULLET:
		break;
	case I_TORPEDO:
		break;
	case I_MISSILE:
		break;
	case I_BOOSTER:
		PlayAnimation(L"Sprites/Item/Boost/boost");
		break;
	case I_TOOLBOX:
		PlayAnimation(L"Sprites/Item/toolbox/toolbox");
		break;
	case I_EVENTBOX:
		PlayAnimation(L"Sprites/Item/eventbox/eventbox");
		break;
	default:
		break;
	}

	position.x -= movespeed * Time::dt;
}

void ItemManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Item* item = new Item;
		item->isactive = false;
		item->player = player;
		it.push_back(item);
	}
}

void ItemManager::Spawn(Vec2 pos, ItemType type)
{
	for (auto iter : it)
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

void ItemManager::Delete()
{
	for (auto iter : it)
	{
		delete iter;
	}
	it.clear();
}
