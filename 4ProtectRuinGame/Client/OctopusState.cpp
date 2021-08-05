#include "DXUT.h"
#include "OctopusState.h"

int
OctopusIdleState::handleInput()
{
	if (object->HP <= 0)
 		return STC(OctopusState::DIE);

	if (true == object->isDamaged)
		return STC(OctopusState::DAMAGED);

	idleTime += Monster::GetDT();

	if (idleTime >= 2)
	{
		idleTime = 0;
		return STC(OctopusState::WALK);
	}

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
	if (true == object->isDamaged)
		return STC(OctopusState::DAMAGED);

	deltatime += Monster::GetDT();

	Player* pl = static_cast<Octopus*>(object)->player;

	if (deltatime > object->attackSpeed)
	{
		if (static_cast<Monster*>(object)->PlayAnimationM(L"octoattack"))
		{
			float distance = fabs(object->collider->position.x - pl->collider->position.x); // 500
			if (distance < 300)
			{
				if (object->collider->position.x < pl->collider->position.x)
				{
					if (true == object->lookingRight)
					{
						pl->GetAttack(object->attackLevel, Vec2(1.f, 0));
					}
				}
				else
				{
					if (false == object->lookingRight)
					{
						pl->GetAttack(object->attackLevel, Vec2(-1.f, 0));
					}
				}
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
	if (true == object->isDamaged)
		return STC(OctopusState::DAMAGED);

	if (false == isWalkStart)
	{
		isWalkStart = true;
		int res = std::rand() % 2;
		object->lookingRight = res;
		xWay = (res == 1 ? 1 : -1);
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
	if (true == object->isDamaged)
	{
		object->gravity = true;
		return STC(OctopusState::DAMAGED);
	}

	float distance = fabs(object->collider->position.x - static_cast<Octopus*>(object)->player->collider->position.x); // 500
	if (distance > 500)
	{
		object->gravity = true;
		return STC(OctopusState::IDLE);
	}
	else if (distance < 300)
	{
		object->gravity = true;
		return STC(OctopusState::ATTACK);
	}

	if (true == object->wallcollided)
	{
		object->collider->position.y -= Monster::GetDT() * 1500.f;
		object->gravity = false;
		object->isonfloor = false;
		delta = 0;
	}
	else
	{
		delta += Monster::GetDT();
		if (delta > 0.3f)
		{
			object->gravity = true;
			delta = 0;
		}
	}
	
	if (object->collider->position.x > static_cast<Octopus*>(object)->player->collider->position.x)
	{
		object->collider->position.x -= Monster::GetDT() * 100.f;
		object->lookingRight = false;
	}
	else
	{
		object->collider->position.x += Monster::GetDT() * 100.f;
		object->lookingRight = true;
	}
	static_cast<Monster*>(object)->PlayAnimationM(L"octowalk");

	return STC(OctopusState::FOLLOW);
}

int OctopusDamagedState::handleInput()
{
	if (static_cast<Monster*>(object)->PlayAnimationM(L"octohurt"))
	{
		object->isDamaged = false;
		return STC(OctopusState::IDLE);
	}
	
	object->collider->position.x += object->pushDirection.x * Monster::GetDT() * 100.f;

	return STC(OctopusState::DAMAGED);
}

int OctopusDieState::handleInput()
{
	if (static_cast<Monster*>(object)->PlayAnimationM(L"octohurt"))
	{
		object->isactive = false;
		object->collider->isactive = false;

		return STC(OctopusState::IDLE);
	}
	return STC(OctopusState::DIE);
}
