#include "DXUT.h"
#include "TileMapManager.h"
#include "Player.h"

Player::Player() 
{
	statechanger = new IdleState(this);
	CreateAnimation(L"run", 6, 0.1f);
	CreateAnimation(L"attack", 3, 0.1f);
	CreateAnimation(L"idle", 2, 0.6f);
	CreateAnimation(L"jump", 2, 0.15f);
	CreateAnimation(L"jumpend", 1, 0.15f);
	PlayAnimation(L"idle");

	collider->scale = { 0.6f, 1 };
}

Player::~Player()
{
	delete statechanger;
}

void
Player::Action()
{
	PlayerStates ps = statechanger->handleInput();

	if (ps != currentstate)
	{
		delete statechanger;
		switch (ps)
		{
		case PlayerStates::IDLE:
			statechanger = new IdleState(this);
			break;
		case PlayerStates::RUN:
			statechanger = new RunState(this);
			break;
		case PlayerStates::ATTACK:
			statechanger = new AttackState(this);
			break;
		case PlayerStates::JUMP:
			statechanger = new JumpState(this);
			break;
		case PlayerStates::JUMPEND:
			statechanger = new JumpEndState(this);
			break;
		default:
			break;
		}
		currentstate = ps;
	}
}
