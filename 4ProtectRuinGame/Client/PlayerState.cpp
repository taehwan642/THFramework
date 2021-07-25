#include "DXUT.h"
#include "MonsterManager.h"
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
		object->lookingRight = false;
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('D')) 
	{ 
		keys[1] = 1; 
		object->collider->position.x += 300.f * DXUTGetElapsedTime();
		object->lookingRight = true;
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
	{
		MonsterManager& mm = MonsterManager::GetInstance();
		for (auto& iter : mm.monsters)
		{
			if (nullptr == iter || iter->isactive == false)
				continue;

			float distance = fabs(object->collider->position.x - iter->collider->position.x);
			
			if (distance <= 300)
			{
				if (object->collider->position.x < iter->collider->position.x)
				{
					if (object->lookingRight == true)
					{
						iter->GetAttack(object->attackLevel);
					}
				}
				else
				{
					if (object->lookingRight == false)
					{
						iter->GetAttack(object->attackLevel);
					}
				}
			}
		}

		return CASTVOIDP(PlayerStates::IDLE);
	}

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
			object->lookingRight = false;
		}
		if (DXUTIsKeyDown('D'))
		{
			object->collider->position.x += 300.f * DXUTGetElapsedTime();
			object->lookingRight = true;
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
		object->lookingRight = false;
	}
	if (DXUTIsKeyDown('D'))
	{
		object->collider->position.x += 300.f * DXUTGetElapsedTime();
		object->lookingRight = true;
	}
	return CASTVOIDP(PlayerStates::JUMPEND);
}

void* 
DamagedState::handleInput()
{
	deltatime += DXUTGetElapsedTime();
	object->gravity = true;
	if (deltatime > 0.3f)
	{
		deltatime = 0;
		object->color = D3DCOLOR_RGBA(255, 255, 255, 255);
		return CASTVOIDP(PlayerStates::IDLE);
	}
	object->color = D3DCOLOR_RGBA(255, 0, 0, 255);

	if (DXUTIsKeyDown('A'))
	{
		object->collider->position.x -= 300.f * DXUTGetElapsedTime();
		object->lookingRight = false;
	}
	if (DXUTIsKeyDown('D'))
	{
		object->collider->position.x += 300.f * DXUTGetElapsedTime();
		object->lookingRight = true;
	}

	return CASTVOIDP(PlayerStates::DAMAGED);
}
