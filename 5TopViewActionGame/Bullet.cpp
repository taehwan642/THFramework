#include "DXUT.h"
#include "Player.h"
#include "Effect.h"
#include "Bullet.h"

void BManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Bullet* b = new Bullet;
		b->player = player;
		b->isactive = false;
		b->layer = 3;
		bullets.push_back(b);
	}
}

void BManager::Spawn(Vec2 pos, Vec2 mousepos, int damage, int spawntype, bool isWeak)
{
	for (auto iter : bullets)
	{
		if (iter->isactive == false)
		{
			if (spawntype == 0)
			{
				Vec2 d = mousepos - pos; // ���⺤��
				D3DXVec2Normalize(&iter->dir, &d);
				// ������
				iter->strValue = damage;
				iter->isactive = true;
				iter->position = pos + iter->dir * 5; // �ѱ������� ���� ������ ����ֱ�
				iter->alivetime = 3.f;
				iter->isWeak = isWeak;
				iter->Lookat(mousepos);
			}
			else
			{
				D3DXVec2Normalize(&iter->dir, &mousepos);
				// ������
				iter->strValue = damage;
				iter->isactive = true;
				iter->position = pos + iter->dir * 5; // �ѱ������� ���� ������ ����ֱ�
				iter->alivetime = 3.f;
				iter->isWeak = isWeak;
				iter->Lookat(-iter->dir, true);
			}
			// dir �������
			
			return;
		}
	}
}

void BManager::Delete()
{
	for (auto iter : bullets)
	{
		delete iter;
	}
	bullets.clear();
}

Bullet::Bullet()
{
	movespeed = 1000.f;
	strValue = 1;
	SetTexture(L"bullet.png");
}

void Bullet::UpGauge()
{
	if(isWeak == true)
		++player->attackgauge;
}

void Bullet::Action()
{
	if (isCollide)
	{
		EManager::GetInstance().Spawn(position, E_HIT);
		isactive = false;
		position = { -999,-999 };
	}

	if (alivetime < 0)
	{
		isactive = false;
		position = { -999,-999 };
	}

	position += dir * movespeed * DXUTGetElapsedTime();
	alivetime -= DXUTGetElapsedTime();
}
