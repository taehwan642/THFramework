#include "DXUT.h"
#include "OctopusState.h"

int
OctopusIdleState::handleInput()
{
	idleTime += Monster::GetDT();

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

	static_cast<Monster*>(object)->PlayAnimationM(L"octoidle");

	return STC(OctopusState::IDLE);
}

int
OctopusAttackState::handleInput()
{
	deltatime += Monster::GetDT();
	object->gravity = true;

	if (deltatime > object->attackSpeed)
	{
		if (static_cast<Monster*>(object)->PlayAnimationM(L"octoattack"))
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
	walktime += Monster::GetDT();

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

	object->collider->position.x += xWay * Monster::GetDT() * 100.f;

	static_cast<Monster*>(object)->PlayAnimationM(L"octowalk");

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
		object->collider->position.y -= Monster::GetDT() * 1500.f;
		object->gravity = false;
		object->isonfloor = false;
	}
	
	if (object->collider->position.x > static_cast<Octopus*>(object)->player->collider->position.x)
	{
		object->collider->position.x -= Monster::GetDT() * 100.f;
	}
	else
	{
		object->collider->position.x += Monster::GetDT() * 100.f;
	}
	static_cast<Monster*>(object)->PlayAnimationM(L"octowalk");

	return STC(OctopusState::FOLLOW);
}
