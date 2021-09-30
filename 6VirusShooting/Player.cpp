#include "DXUT.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Player.h"

Player::Player()
{
	layer = 30;
	CreateAnimation(L"Sprites/player/move/6/move", 30, 0.05f);
	PlayAnimation(L"Sprites/player/move/6/move");

	position = MIDDLE;

	movespeed = 300;
	scale = { 0.3,0.3 };
	weapons.push_back(new MachineGun);
	weapons.push_back(new NavalGun);
	weapons.push_back(new TorpedoLauncher);
	weapons.push_back(new MissileLauncher);
}

Player::~Player()
{
	for (auto iter : weapons)
		delete iter;
	weapons.clear();
}

void Player::Shoot()
{
	// 가장 근접한 유닛 구하는 방법
	// Monster 
	
	

	// pos은 뭐다? 쏘는 위치
	// dir은 뭐다? 날라가가는 방향
	// 즉 가장 근접한 유닛으로의 방향이
	weapons[currentWeapon]->Shoot(position);
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

	if (speedbuffTime > 0)
	{
		movespeed = 300.f + speedbuffValue;
		if (speedbuffValue > 0)
			color = D3DCOLOR_RGBA(128, 128, 255, 255);
		else
			color = D3DCOLOR_RGBA(255, 128, 128, 255);
	}
	else
	{
		movespeed = 300.f;
		color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	
	Shoot();

	if (DXUTWasKeyPressed('1'))
		currentWeapon = 0;
	if (DXUTWasKeyPressed('2'))
		currentWeapon = 1;

	PlayAnimation(L"Sprites/player/move/6/move");
	Move();
}
