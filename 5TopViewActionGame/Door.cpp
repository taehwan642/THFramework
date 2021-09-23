#include "DXUT.h"
#include "Monster.h"
#include "MonsterSpawner.h"
#include "TileMapManager.h"
#include "Door.h"

Door::Door()
{
	scale = { TileMapManager::GetInstance().blockScale, TileMapManager::GetInstance().blockScale };
	layer = 30;
}

std::wstring Door::SetDoorTexture(int doorIndex)
{
	std::wstring tex;
	currentDoorTexture = doorIndex;
	if (false == isOpen)
	{
		switch (doorIndex)
		{
		case DOOR1:
			tex = L"door.png";
			break;
		case DOOR2:
			tex = L"door2.png";
			break;
		case DOOR3:
			tex = L"door3.png";
			break;
		case DOOR4:
			tex = L"door4.png";
			break;
		default:
			break;
		}
	}
	else
	{
		switch (doorIndex)
		{
		case DOOR1:
			tex = L"open_door.png";
			break;
		case DOOR2:
			tex = L"open_door2.png";
			break;
		case DOOR3:
			tex = L"open_door3.png";
			break;
		case DOOR4:
			tex = L"open_door4.png";
			break;
		default:
			break;
		}
	}
	
	return tex;
}

void Door::CheckOpen()
{
	MonsterManager& mm = MonsterManager::GetInstance();
	MonsterSpawnerManager& msm = MonsterSpawnerManager::GetInstance();

	bool canbeopen = true;

	for (auto iter : mm.monsters)
	{
		if (nullptr == iter)
			continue;

		if (iter->isactive == true)
		{
			canbeopen = false;
			break;
		}
	}

	for (auto iter : msm.spn)
	{
		if (iter->isactive == true)
		{
			if (iter->monsterSpawnValue != 0)
			{
				canbeopen = false;
				break;
			}
		}
	}
	isOpen = canbeopen;
	if (isOpen == true)
		SetTexture(SetDoorTexture(currentDoorTexture));
}

bool Door::CollisionPlayer(Vec2 pos)
{
	// �����մ� ���¿���
	// Ŭ���̴� ���� �̤����� ��� ����
	Vec2 dist = pos - position; // ������ -> �÷��̾�? �÷��̾� -> ��?
	float length = D3DXVec2Length(&dist); // ������ ����

	if (isOpen == true && length < 130.f)
	{
		return true;
	}

	return false;
}

void Door::Update()
{
	CheckOpen();
}
