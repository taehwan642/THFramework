#include "DXUT.h"
#include "OctopusState.h"

void* OctopusIdleState::handleInput()
{
	idleTime += DXUTGetElapsedTime();

	if (idleTime >= 2)
	{
		idleTime = 0;
		return CASTVOIDP(OctopusState::WALK);
	}

	object->gravity = true;

	float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
	if (distance < 500)
	{
		return CASTVOIDP(OctopusState::FOLLOW);
	}

	object->PlayAnimation(L"octoidle");

	return CASTVOIDP(OctopusState::IDLE);
}

void* OctopusAttackState::handleInput()
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
			return CASTVOIDP(OctopusState::IDLE);
		}
	}
	return CASTVOIDP(OctopusState::ATTACK);
}

void* OctopusWalkState::handleInput()
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
		return CASTVOIDP(OctopusState::IDLE);
	}

	if (true == object->wallcollided)
	{
		xWay *= -1;
	}

	object->collider->position.x += xWay * DXUTGetElapsedTime() * 100.f;

	object->PlayAnimation(L"octowalk");

	return CASTVOIDP(OctopusState::WALK);
}

void* OctopusFollowState::handleInput()
{
	float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
	if (distance > 500)
	{
		return CASTVOIDP(OctopusState::IDLE);
	}
	else if (distance < 300)
	{
		return CASTVOIDP(OctopusState::ATTACK);
	}

	if (true == object->wallcollided)
	{
		object->collider->position.y -= DXUTGetElapsedTime() * 300.f;
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

	return CASTVOIDP(OctopusState::FOLLOW);
}
