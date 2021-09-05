#include "DXUT.h"
#include "Player.h"

void Player::Heal(int healvalue)
{
	hp += healvalue;
	if (hp > PLAYERMAXHP)
	{
		hp = PLAYERMAXHP;
	}
}

Player::Player()
{
	movespeed = 300;
	hp = PLAYERMAXHP;
}

void Player::Move()
{
	if (DXUTWasKeyPressed('E'))
		--score;
	if (DXUTWasKeyPressed('Q'))
		++score;

	if (isAttacking)
		return;

	if (DXUTIsKeyDown('W'))
		position.y -= DXUTGetElapsedTime() * movespeed;
	if (DXUTIsKeyDown('A'))
		position.x -= DXUTGetElapsedTime() * movespeed;
	if (DXUTIsKeyDown('S'))
		position.y += DXUTGetElapsedTime() * movespeed;
	if (DXUTIsKeyDown('D'))
		position.x += DXUTGetElapsedTime() * movespeed;
}

void Player::Action()
{
	Move();
}
