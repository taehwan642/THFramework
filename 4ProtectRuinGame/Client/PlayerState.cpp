#include "DXUT.h"
#include "PlayerState.h"

void*
IdleState::handleInput()
{
	if (DXUTIsKeyDown('A')
		|| DXUTIsKeyDown('D'))
		return CASTVOIDP(PlayerStates::RUN);

	if (DXUTIsKeyDown('W') && object->isonfloor == true)
		return CASTVOIDP(PlayerStates::JUMP);

	if (DXUTIsKeyDown(VK_SPACE))
		return CASTVOIDP(PlayerStates::ATTACK);

	object->PlayAnimation(L"idle");

	return CASTVOIDP(PlayerStates::IDLE);
}

void*
RunState::handleInput()
{
	if (DXUTIsKeyDown('A'))
	{
		keys[0] = 1;
		object->collider->position.x -= 300.f * DXUTGetElapsedTime();
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('D')) 
	{ 
		keys[1] = 1; 
		object->collider->position.x += 300.f * DXUTGetElapsedTime();
	}
	else keys[1] = 0;

	int result = keys[0] + keys[1];

	if (result == 0)
		return CASTVOIDP(PlayerStates::IDLE);

	if (DXUTIsKeyDown('W') && object->isonfloor == true)
		return CASTVOIDP(PlayerStates::JUMP);

	if (DXUTWasKeyPressed(VK_SPACE))
		return CASTVOIDP(PlayerStates::ATTACK);

	object->PlayAnimation(L"run");

	return CASTVOIDP(PlayerStates::RUN);
}

void*
AttackState::handleInput()
{
	if (object->PlayAnimation(L"attack"))
		return CASTVOIDP(PlayerStates::IDLE);
	return CASTVOIDP(PlayerStates::ATTACK);
}

void*
JumpState::handleInput()
{
	if (object->PlayAnimation(L"jump"))
	{
		object->gravity = true;
		return CASTVOIDP(PlayerStates::JUMPEND);
	}
	else
	{
		object->gravity = false;
		object->isonfloor = false;
		object->collider->position.y -= 500.f * DXUTGetElapsedTime();
		if (DXUTIsKeyDown('A'))
		{
			object->collider->position.x -= 300.f * DXUTGetElapsedTime();
		}
		if (DXUTIsKeyDown('D'))
		{
			object->collider->position.x += 300.f * DXUTGetElapsedTime();
		}
	}

	return CASTVOIDP(PlayerStates::JUMP);
}

void*
JumpEndState::handleInput()
{
	if (object->isonfloor)
	{
		if (object->PlayAnimation(L"jumpend"))
			return CASTVOIDP(PlayerStates::IDLE);
	}
	if (DXUTIsKeyDown('A'))
	{
		object->collider->position.x -= 300.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('D'))
	{
		object->collider->position.x += 300.f * DXUTGetElapsedTime();
	}
	return CASTVOIDP(PlayerStates::JUMPEND);
}
