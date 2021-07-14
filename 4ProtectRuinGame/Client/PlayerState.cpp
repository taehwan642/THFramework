#include "DXUT.h"
#include "PlayerState.h"

PlayerStates 
IdleState::handleInput()
{
	if (DXUTIsKeyDown('A')
		|| DXUTIsKeyDown('D'))
		return PlayerStates::RUN;

	if (DXUTIsKeyDown('W'))
		return PlayerStates::JUMP;

	if (DXUTIsKeyDown(VK_SPACE))
		return PlayerStates::ATTACK;

	player->PlayAnimation(L"idle");

	return PlayerStates::IDLE;
}

PlayerStates 
RunState::handleInput()
{
	if (DXUTIsKeyDown('A'))
	{
		keys[0] = 1;
		player->position.x -= 300.f * DXUTGetElapsedTime();
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('D')) 
	{ 
		keys[1] = 1; 
		player->position.x += 300.f * DXUTGetElapsedTime();
	}
	else keys[1] = 0;

	int result = keys[0] + keys[1];

	if (result == 0)
		return PlayerStates::IDLE;

	if (DXUTIsKeyDown('W'))
		return PlayerStates::JUMP;

	if (DXUTWasKeyPressed(VK_SPACE))
		return PlayerStates::ATTACK;

	player->PlayAnimation(L"run");

	return PlayerStates::RUN;
}

PlayerStates 
AttackState::handleInput()
{
	if (player->PlayAnimation(L"attack"))
		return PlayerStates::IDLE;
	return PlayerStates::ATTACK;
}

PlayerStates JumpState::handleInput()
{
	if (player->PlayAnimation(L"jump"))
		return PlayerStates::IDLE;
	else
	{
		// ¶Ù±â
	}

	return PlayerStates::JUMP;
}