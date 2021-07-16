#include "DXUT.h"
#include "PlayerState.h"

PlayerStates 
IdleState::handleInput()
{
	if (DXUTIsKeyDown('A')
		|| DXUTIsKeyDown('D'))
		return PlayerStates::RUN;

	if (DXUTIsKeyDown('W') && player->isonfloor == true)
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
		player->collider->position.x -= 300.f * DXUTGetElapsedTime();
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('D')) 
	{ 
		keys[1] = 1; 
		player->collider->position.x += 300.f * DXUTGetElapsedTime();
	}
	else keys[1] = 0;

	int result = keys[0] + keys[1];

	if (result == 0)
		return PlayerStates::IDLE;

	if (DXUTIsKeyDown('W') && player->isonfloor == true)
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

PlayerStates 
JumpState::handleInput()
{
	if (player->PlayAnimation(L"jump"))
	{
		player->gravity = true;
		return PlayerStates::JUMPEND;
	}
	else
	{
		player->gravity = false;
		player->isonfloor = false;
		player->collider->position.y -= 500.f * DXUTGetElapsedTime();
		if (DXUTIsKeyDown('A'))
		{
			player->collider->position.x -= 300.f * DXUTGetElapsedTime();
		}
		if (DXUTIsKeyDown('D'))
		{
			player->collider->position.x += 300.f * DXUTGetElapsedTime();
		}
	}

	return PlayerStates::JUMP;
}

PlayerStates 
JumpEndState::handleInput()
{
	if (player->isonfloor)
	{
		if (player->PlayAnimation(L"jumpend"))
			return PlayerStates::IDLE;
	}
	if (DXUTIsKeyDown('A'))
	{
		player->collider->position.x -= 300.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('D'))
	{
		player->collider->position.x += 300.f * DXUTGetElapsedTime();
	}
	return PlayerStates::JUMPEND;
}
