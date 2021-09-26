#include "DXUT.h"
#include "Player.h"
#include "SceneManager.h"
#include "MonsterBullet.h"
#include "TileMapManager.h"
#include "Boss1.h"

Boss1::Boss1()
{
	CreateAnimation(L"boss1idle", 10, 0.1f);
	CreateAnimation(L"boss1att", 4, 0.3f);
	PlayAnimation(L"boss1idle");
	hpui->SetTexture(L"boss1hpui.png");
	layer = 100;
	maxHP = 20;
	scale = { 1,1 };
}

Boss1::~Boss1()
{
	
}

void Boss1::Dead()
{

}

void Boss1::Follow()
{
	if (dontmoveTime > 0)
		return;

	// 방향 벡터 구하기
	Vec2 dir = player->position - position;
	D3DXVec2Normalize(&dir, &dir);

	position += dir * SM GetDeltaTime() * movespeed;
}

void Boss1::CheckCanAttack()
{
	Vec2 distance = player->position - position;
	float length = D3DXVec2Length(&distance);
	
	if (length < 300.f) // 일반 총알쏘기 + 일직선
	{
		pattern = rand() % 2;
		state = M_ATTACK;
		dontmoveTime = 1.f;
	}
	else if (length < 600.f) // 600 일직선
	{
		pattern = 1;
		state = M_ATTACK;
		dontmoveTime = 1.f;
	}
	
}

void Boss1::SetStat(int diff)
{
	hp = maxHP + (diff - 1) * 5;
	strValue = 1 + diff - 1;
}

bool Boss1::IdleState()
{
	PlayAnimation(L"boss1idle");
	return true;
}

bool Boss1::AttackState()
{
	if (PlayAnimation(L"boss1att"))
	{
		Vec2 dir = player->position - position;
		D3DXVec2Normalize(&dir, &dir);

		MonsterBulletManager::GetInstance().Spawn(position + dir * 150,
			Vec2(player->position - position), strValue, BOSS1);
		return true;
	}
	return false;
}
