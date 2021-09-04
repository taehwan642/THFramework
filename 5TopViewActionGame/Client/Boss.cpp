#include "DXUT.h"
#include "Boss.h"

Boss::Boss(Player* p) : 
	Monster(p)
{
	CreateAnimation(L"flyidle", 2, 0.1f);
	PlayAnimation(L"flyidle");

	stm->AddState(STC(BossState::IDLE), new BossIdleState(this));
	stm->AddState(STC(BossState::WALK), new BossWalkState(this));
	stm->AddState(STC(BossState::FOLLOW), new BossFollowState(this));
	stm->ChangeState(STC(BossState::IDLE));

	scale = { 2,2 };
	collider->scale = { 1.5f, 2 };
	gravity = false;
}

Boss::~Boss()
{
}

void Boss::Action()
{
}
