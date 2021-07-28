#include "DXUT.h"
#include "MonsterManager.h"
#include "PlayerState.h"

int
IdleState::handleInput()
{
	if (DXUTIsKeyDown('A')
		|| DXUTIsKeyDown('D'))
		return STC(PlayerStates::RUN);

	if (DXUTIsKeyDown('W') && object->isonfloor == true)
		return STC(PlayerStates::JUMP);

	if (DXUTIsKeyDown(VK_SPACE))
		return STC(PlayerStates::ATTACK);

	if (DXUTIsKeyDown(VK_LSHIFT))
		return STC(PlayerStates::DODGE);

	object->PlayAnimation(L"idle");

	return STC(PlayerStates::IDLE);
}

int
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
		return STC(PlayerStates::IDLE);

	if (DXUTIsKeyDown('W') && object->isonfloor == true)
		return STC(PlayerStates::JUMP);

	if (DXUTWasKeyPressed(VK_SPACE))
		return STC(PlayerStates::ATTACK);

	object->PlayAnimation(L"run");

	return STC(PlayerStates::RUN);
}

int
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

		return STC(PlayerStates::IDLE);
	}

	return STC(PlayerStates::ATTACK);
}

int
JumpState::handleInput()
{
	if (object->PlayAnimation(L"jump"))
	{
		object->gravity = true;
		return STC(PlayerStates::JUMPEND);
	}
	else
	{
		object->gravity = false;
		object->isonfloor = false;
		object->collider->position.y -= 1500.f * DXUTGetElapsedTime();
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

	return STC(PlayerStates::JUMP);
}

int
JumpEndState::handleInput()
{
	if (object->isonfloor)
	{
		if (object->PlayAnimation(L"jumpend"))
			return STC(PlayerStates::IDLE);
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
	return STC(PlayerStates::JUMPEND);
}

int
DamagedState::handleInput()
{
	deltatime += DXUTGetElapsedTime();
	object->gravity = true;
	if (deltatime > 0.3f)
	{
		deltatime = 0;
		object->color = D3DCOLOR_RGBA(255, 255, 255, 255);
		return STC(PlayerStates::IDLE);
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

	return STC(PlayerStates::DAMAGED);
}

int DodgeState::handleInput()
{
	if (object->PlayAnimation(L"roll"))
	{
		static_cast<Player*>(object)->isDodging = false;
		return STC(PlayerStates::IDLE);
	}
	int xWay = (true == object->lookingRight) ? 1 : -1;
	object->collider->position.x += xWay * DXUTGetElapsedTime() * 300.f;
	static_cast<Player*>(object)->isDodging = true;
	return STC(PlayerStates::DODGE);
}
