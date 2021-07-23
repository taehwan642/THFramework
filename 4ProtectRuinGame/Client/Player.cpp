#include "DXUT.h"
#include "TileMapManager.h"
#include "Player.h"

Player::Player() 
{
	CreateAnimation(L"run", 6, 0.1f);
	CreateAnimation(L"attack", 3, 0.1f);
	CreateAnimation(L"idle", 2, 0.6f);
	CreateAnimation(L"jump", 2, 0.15f);
	CreateAnimation(L"jumpend", 1, 0.15f);
	PlayAnimation(L"idle");

	collider->scale = { 0.6f, 1 };

	stm->AddState(CASTVOIDP(PlayerStates::IDLE), new IdleState(this));
	stm->AddState(CASTVOIDP(PlayerStates::RUN), new RunState(this));
	stm->AddState(CASTVOIDP(PlayerStates::JUMP), new JumpState(this));
	stm->AddState(CASTVOIDP(PlayerStates::JUMPEND), new JumpEndState(this));
	stm->AddState(CASTVOIDP(PlayerStates::ATTACK), new AttackState(this));
	stm->ChangeState(CASTVOIDP(PlayerStates::IDLE));
}

Player::~Player()
{
}

void
Player::Action()
{
}
