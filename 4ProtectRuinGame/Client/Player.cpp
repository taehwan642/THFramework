#include "DXUT.h"
#include "MonsterManager.h"
#include "TileMapManager.h"
#include "Player.h"

Player::Player() 
{
	CreateAnimation(L"run", 6, 0.1f);
	CreateAnimation(L"attack", 3, 0.1f);
	CreateAnimation(L"idle", 2, 0.6f);
	CreateAnimation(L"jump", 2, 0.15f);
	CreateAnimation(L"jumpend", 1, 0.15f);
	CreateAnimation(L"roll", 5, 0.07f);
	CreateAnimation(L"super", 2, 0.3f);
	CreateAnimation(L"hurt", 2, 0.1f);
	PlayAnimation(L"idle");

	collider->scale = { 0.6f, 1 };

	stm->AddState(STC(PlayerStates::IDLE), new IdleState(this));
	stm->AddState(STC(PlayerStates::RUN), new RunState(this));
	stm->AddState(STC(PlayerStates::JUMP), new JumpState(this));
	stm->AddState(STC(PlayerStates::JUMPEND), new JumpEndState(this));
	stm->AddState(STC(PlayerStates::ATTACK), new AttackState(this));
	stm->AddState(STC(PlayerStates::DAMAGED), new DamagedState(this));
	stm->AddState(STC(PlayerStates::DODGE), new DodgeState(this));
	stm->AddState(STC(PlayerStates::SUPER), new SuperState(this));
	stm->ChangeState(STC(PlayerStates::IDLE));

	hpbar = new HPUI(L"playerUI.png", L"playerUIBar.png");

	hpbar->SetMaxHP(MaxHP);
	hpbar->SetHP(HP);

	hpbar->SetUp(240);
}

Player::~Player()
{
}

void
Player::Action()
{
	MonsterManager& mm = MonsterManager::GetInstance();
	for (auto& iter : mm.monsters)
	{
		if (nullptr == iter ||iter->isactive == false)
			continue;
		
		RECT temp;
		if (IntersectRect(&temp, &collider->GetRect(), &iter->collider->GetRect()))
		{
			Vec2 dir = Vec2(1.f, 0.f);
			if (collider->position.x < iter->collider->position.x)
				dir.x *= -1.f;
			GetAttack(iter->attackLevel, dir);
		}
	}
	hpbar->SetHP(HP);

}

bool 
Player::Check_CanGetAttack()
{
	if (true == isDodging)
		return false;
	return true;
}
