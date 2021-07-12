#include "DXUT.h"
#include "PlayerState.h"

PlayerStates 
IdleState::handleInput()
{
	if (DXUTWasKeyPressed('W')
		|| DXUTWasKeyPressed('A')
		|| DXUTWasKeyPressed('S')
		|| DXUTWasKeyPressed('D'))
	{
		return PlayerStates::RUN;
	}

	if (DXUTWasKeyPressed(VK_SPACE))
		return PlayerStates::ATTACK;

	player->PlayAnimation(L"idle");

	return PlayerStates::IDLE;
}

PlayerStates 
RunState::handleInput()
{
	if (DXUTIsKeyDown('W'))
	{
		keys[0] = 1;
		player->position.y -= 300.f * DXUTGetElapsedTime();
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('A'))
	{
		keys[1] = 1;
		player->position.x -= 300.f * DXUTGetElapsedTime();
	}
	else keys[1] = 0;

	if (DXUTIsKeyDown('S')) 
	{ 
		keys[2] = 1;
		player->position.y += 300.f * DXUTGetElapsedTime();
	}
	else keys[2] = 0;

	if (DXUTIsKeyDown('D')) 
	{ 
		keys[3] = 1; 
		player->position.x += 300.f * DXUTGetElapsedTime();
	}
	else keys[3] = 0;

	int result = keys[0] + keys[1] + keys[2] + keys[3];

	if (result == 0)
		return PlayerStates::IDLE;

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