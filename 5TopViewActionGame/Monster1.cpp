#include "DXUT.h"
#include "Player.h"
#include "Effect.h"
#include "Monster1.h"

Monster1::Monster1()
{
	CreateAnimation(L"m1idle", 4, 0.1f);
	CreateAnimation(L"m1att", 5, 0.1f);
	PlayAnimation(L"m1att");
	layer = 100;
	position = { screenwidth / 2, screenheight / 2 };
	hpui->SetTexture(L"Enemy_HP.png");
	maxHP = 5;
}

Monster1::~Monster1()
{

}

void Monster1::Dead()
{
	EManager::GetInstance().Spawn(position, E_MDIE);
	hpui->isactive = false;
	hpuibar->isactive = false;
	player->score += 30;
}

void Monster1::Follow()
{
	if (dontmoveTime > 0)
		return;

	// 방향 벡터 구하기
	Vec2 dir = player->position - position;
	D3DXVec2Normalize(&dir, &dir);

	position += dir;
}

void Monster1::Attack()
{
	// x, y의 거리가 들어갔다.
	Vec2 distance = player->position - position;
	float length = D3DXVec2Length(&distance);
	if (length < 150.f)
	{
		state = M_ATTACK;
		dontmoveTime = 0.5f;
	}
}

bool Monster1::IdleState()
{
	PlayAnimation(L"m1idle");
	return true;
}

bool Monster1::AttackState()
{
	if (PlayAnimation(L"m1att"))
	{
		Vec2 distance = player->position - position;
		float length = D3DXVec2Length(&distance);
		if (length < 150.f)
		{
			// 맞는다
			player->Damaged(strValue);
		}
		return true;
	}
	return false;
}

void Monster1::SetStat(int diff)
{
	hp = maxHP + ((diff - 1) * 1.5f);
	strValue = 1 + ((diff - 1) * 1.5f);
}
