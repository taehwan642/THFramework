#include "DXUT.h"
#include "OctopusState.h"

int
OctopusIdleState::handleInput()
{
	idleTime += DXUTGetElapsedTime();

	if (idleTime >= 2)
	{
		idleTime = 0;
		return STC(OctopusState::WALK);
	}

	object->gravity = true;

	float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
	if (distance < 500)
	{
		return STC(OctopusState::FOLLOW);
	}

	object->PlayAnimation(L"octoidle");

	return STC(OctopusState::IDLE);
}

int
OctopusAttackState::handleInput()
{
	deltatime += DXUTGetElapsedTime();
	object->gravity = true;

	if (deltatime > object->attackSpeed)
	{
		if (object->PlayAnimation(L"octoattack"))
		{
			float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
			if (distance < 300)
			{
				static_cast<Octopus*>(object)->player->GetAttack(object->attackLevel);
			}
			deltatime = 0;
			return STC(OctopusState::IDLE);
		}
	}
	return STC(OctopusState::ATTACK);
}

int
OctopusWalkState::handleInput()
{
	if (false == isWalkStart)
	{
		isWalkStart = true;
		int res = std::rand() % 2;
		xWay = (res == 0 ? 1 : -1);
	}
	walktime += DXUTGetElapsedTime();

	if (walktime >= 1)
	{
		walktime = 0;
		isWalkStart = false;
		return STC(OctopusState::IDLE);
	}

	if (true == object->wallcollided)
	{
		xWay *= -1;
	}

	object->collider->position.x += xWay * DXUTGetElapsedTime() * 100.f;

	object->PlayAnimation(L"octowalk");

	return STC(OctopusState::WALK);
}

int
OctopusFollowState::handleInput()
{
	float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
	if (distance > 500)
	{
		return STC(OctopusState::IDLE);
	}
	else if (distance < 300)
	{
		return STC(OctopusState::ATTACK);
	}

	if (true == object->wallcollided)
	{
		object->collider->position.y -= DXUTGetElapsedTime() * 1500.f;
		object->gravity = false;
		object->isonfloor = false;
	}
	
	if (object->collider->position.x > static_cast<Octopus*>(object)->player->collider->position.x)
	{
		object->collider->position.x -= DXUTGetElapsedTime() * 100.f;
	}
	else
	{
		object->collider->position.x += DXUTGetElapsedTime() * 100.f;
	}
	object->PlayAnimation(L"octowalk");

	return STC(OctopusState::FOLLOW);
}
