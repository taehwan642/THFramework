#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	SetTexture(L"1.png");
	statechanger = new IdleState;
}

Player::~Player()
{
	delete statechanger;
}

void 
Player::Update()
{
	PlayerStates ps = statechanger->handleInput();
	if (ps != currentstate)
	{
		delete statechanger;
		switch (ps)
		{
		case PlayerStates::IDLE:
			statechanger = new IdleState;
			break;
		case PlayerStates::RUN:
			statechanger = new RunState;
			break;
		case PlayerStates::ATTACK:
			statechanger = new AttackState;
			break;
		default:
			break;
		}
		currentstate = ps;
	}

	std::cout << static_cast<int>(ps) << std::endl;
}
