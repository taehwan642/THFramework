#include "DXUT.h"
#include "Bullet.h"
#include "Player.h"

Player::Player()
{
	layer = 30;
	CreateAnimation(L"Sprites/player/move/6/move", 30, 0.05f);
	PlayAnimation(L"Sprites/player/move/6/move");

	position = MIDDLE;

	movespeed = 300;
	scale = { 0.3,0.3 };
}

void Player::Damaged(int damage)
{
	if (invincibleTime > 0)
		return;

	hp -= damage;
	invincibleTime = 0.5f;
	if (hp <= 0)
	{
		isdead = true;
		Dead();
	}
}

void Player::Move()
{
	if (DXUTIsKeyDown('W'))
	{
		position.y -= movespeed * Time::dt;
	}

	if (DXUTIsKeyDown('S'))
	{
		position.y += movespeed * Time::dt;
	}

	if (DXUTIsKeyDown('A'))
	{
		position.x -= movespeed * Time::dt;
	}

	if (DXUTIsKeyDown('D'))
	{
		position.x += movespeed * Time::dt;
	}
}

void Player::Action()
{
	invincibleTime -= Time::dt;
	speedbuffTime -= Time::dt;
	
	if (invincibleTime > 0) color = D3DCOLOR_RGBA(128, 128, 128, 255);
	else color = D3DCOLOR_RGBA(255, 255, 255, 255);

	if (speedbuffTime > 0) movespeed = 500.f;
	else movespeed = 300.f;
	
	if (DXUTWasKeyPressed(VK_SPACE))
		BulletManager::GetInstance().Spawn(position, Vec2(1, 0), B_NAVALGUNBULLET);

	PlayAnimation(L"Sprites/player/move/6/move");
	Move();
}
