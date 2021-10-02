#include "DXUT.h"
#include "Player.h"
#include "MessageBoy.h"
#include "Weapon.h"
#include "Item.h"

void Item::MachineGunBullet()
{
	// �÷��̾� �� weapon�ȿ�
	// ���� ã�� �Ű� �ŰŰ� �Ű� �ִٸ�
	// currentbullet+=30;
	for (int i = 0; i < player->weapons.size(); ++i)
	{
		if (dynamic_cast<MachineGun*>(player->weapons[i]) != nullptr)
		{
			player->weapons[i]->currentBullet += 30;
			if (player->weapons[i]->currentBullet > 180)
				player->weapons[i]->currentBullet = 180;
			break;
		}
	}
	MessageBoy::GetInstance().SpawnBoy("�ӽŰ� �Ѿ�\n ȹ��!");
}

void Item::Torpedo()
{
	for (int i = 0; i < player->weapons.size(); ++i)
	{
		if (dynamic_cast<TorpedoLauncher*>(player->weapons[i]) != nullptr)
		{
			player->weapons[i]->currentBullet += 5;
			if (player->weapons[i]->currentBullet > 15)
				player->weapons[i]->currentBullet = 15;
			break;
		}
	}
	MessageBoy::GetInstance().SpawnBoy("��� ȹ��!");
}

void Item::Missile()
{
	for (int i = 0; i < player->weapons.size(); ++i)
	{
		if (dynamic_cast<MissileLauncher*>(player->weapons[i]) != nullptr)
		{
			player->weapons[i]->currentBullet += 3;
			if (player->weapons[i]->currentBullet > 10)
				player->weapons[i]->currentBullet = 10;
			break;
		}
	}
	MessageBoy::GetInstance().SpawnBoy("�̻��� ȹ��!");
}

void Item::Booster()
{
	player->speedbuffValue = 200.f;
	player->speedbuffTime = 2.f;
	MessageBoy::GetInstance().SpawnBoy("�ν��� ȹ��!");
}

void Item::Toolbox()
{
	++player->hp;
	if (player->maxHP <= player->hp)
	{
		player->hp = player->maxHP;
	}
	MessageBoy::GetInstance().SpawnBoy("�������� ȹ��!");
}

void Item::Eventbox()
{
	player->invincibleTime = 2.f;
	MessageBoy::GetInstance().SpawnBoy("�̺�Ʈ���� ȹ��!");
}

void Item::CollideWithPlayer()
{
	Vec2 dist = player->position - position;
	float length = D3DXVec2Length(&dist);
	if (length < 100.f)
	{
		switch (type)
		{
		case I_MACHINEGUNBULLET:
			MachineGunBullet();
			break;
		case I_TORPEDO:
			Torpedo();
			break;
		case I_MISSILE:
			Missile();
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
	CreateAnimation(L"Sprites/Item/machinegun/machine", 30, 0.05f);
	CreateAnimation(L"Sprites/Item/missile/missile", 30, 0.05);
	CreateAnimation(L"Sprites/Item/Torpedo/torpedo", 30, 0.05);
}

void Item::Update()
{
	CollideWithPlayer();
	switch (type)
	{
	case I_MACHINEGUNBULLET:
		PlayAnimation(L"Sprites/Item/machinegun/machine");
		break;
	case I_TORPEDO:
		PlayAnimation(L"Sprites/Item/Torpedo/torpedo");
		break;
	case I_MISSILE:
		PlayAnimation(L"Sprites/Item/missile/missile");
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
	if (position.x > screenwidth + 100 ||
		position.x < -100 ||
		position.y > screenheight + 100 ||
		position.y < -100)
	{
		isactive = false;
	}
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
