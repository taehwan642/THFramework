#include "DXUT.h"
#include "Bullet.h"

void BManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Bullet* b = new Bullet;
		b->isactive = false;
		b->layer = 3;
		bullets.push_back(b);
	}
}

void BManager::Spawn(Vec2 pos, Vec2 mousepos, int damage)
{
	for (auto iter : bullets)
	{
		if (iter->isactive == false)
		{
			// dir �������
			Vec2 d = mousepos - pos; // ���⺤��
			D3DXVec2Normalize(&iter->dir, &d);
			// ������
			iter->damage = damage;
			iter->isactive = true;
			iter->position = pos + iter->dir * 5; // �ѱ������� ���� ������ ����ֱ�
			iter->alivetime = 3.f;
			iter->Lookat(mousepos);

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
	SetTexture(L"bullet.png");
}

void Bullet::Update()
{
	position += dir * speed * DXUTGetElapsedTime();
	alivetime -= DXUTGetElapsedTime();
	if (alivetime < 0)
	{
		isactive = false;
	}
}
