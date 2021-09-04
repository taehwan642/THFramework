#include "DXUT.h"
#include "BossState.h"

void Move(GameObject* obj)
{
	static float runningTime = 0.f;
	float speed = 3.f;
	float radius = 3.f;
	runningTime += Monster::GetDT() * speed;

	float result = radius * cos(runningTime);

	
	obj->collider->position.y += result;
}

int BossIdleState::handleInput()
{
	float distance = fabs(object->collider->position.x - static_cast<Monster*>(object)->player->collider->position.x); // 500
	if (distance < 500)
	{
		return STC(BossState::FOLLOW);
	}

	idletime += Monster::GetDT();
	if (idletime > 2)
	{
		idletime = 0;
		return STC(BossState::WALK);
	}
	object->PlayAnimation(L"flyidle");
	Move(object);
	return STC(BossState::IDLE);
}

int BossWalkState::handleInput()
{
	float distance = fabs(object->collider->position.x - static_cast<Monster*>(object)->player->collider->position.x); // 500
	if (distance < 500)
	{
		return STC(BossState::FOLLOW);
	}

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
		return STC(BossState::IDLE);
	}

	if (true == object->wallcollided)
	{
		xWay *= -1;
	}

	object->collider->position.x += xWay * Monster::GetDT() * 100.f;

	object->PlayAnimation(L"flyidle");
	Move(object);
	return STC(BossState::WALK);
}

int BossFollowState::handleInput()
{
	float distance = fabs(object->collider->position.x - static_cast<Monster*>(object)->player->collider->position.x); // 500
	if (distance > 500)
	{
		return STC(BossState::IDLE);
	}
	else if (distance < 300)
	{
		return STC(BossState::ATTACK);
	}
	
	if (object->collider->position.x > static_cast<Monster*>(object)->player->collider->position.x)
	{
		object->collider->position.x -= Monster::GetDT() * 100.f;
		object->lookingRight = false;
	}
	else
	{
		object->collider->position.x += Monster::GetDT() * 100.f;
		object->lookingRight = true;
	}
	object->PlayAnimation(L"flyidle");
	Move(object);
	return STC(BossState::FOLLOW);
}
