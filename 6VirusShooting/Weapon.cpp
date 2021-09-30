#include "DXUT.h"
#include "Bullet.h"
#include "Obsticle.h"
#include "Weapon.h"

MachineGun::MachineGun()
{
	currentBullet = 30;
	shootdelay = 0.05f;
	reloadtime = 5.f;
	autoReload = true;
}

void MachineGun::Shoot(Vec2 pos)
{
	shootdelay -= Time::dt;
	if (shootdelay < 0 && currentBullet > 0)
	{
		std::vector<Vec2> dirs = CheckShoot(pos);
		if (dirs.size() > 0)
		{
			Vec2 lastdir;
			D3DXVec2Normalize(&lastdir, &dirs[dirs.size() - 1]);
			BulletManager::GetInstance().Spawn(pos, lastdir, B_MACHINEGUNBULLET);
			shootdelay = 0.05f;
			--currentBullet;
		}
	}

	if (currentBullet <= 0)
	{
		reloadtime -= Time::dt;
		if (reloadtime < 0)
		{
			reloadtime = 5.f;
			currentBullet = 30;
		}
	}
}

NavalGun::NavalGun()
{
	currentBullet = 5;
	shootdelay = 0.5f;
	reloadtime = 1.f;
}

void NavalGun::Shoot(Vec2 pos)
{
	shootdelay -= Time::dt;
	if (shootdelay < 0)
	{
		std::vector<Vec2> dirs = CheckShoot(pos);
		if (dirs.size() <= 0)
		{
			if (currentBullet > 0)
			{
				// 전부 x는 양수
				float x = (rand() % 10);
				// y 1, -1 
				int d = rand() % 2; // 0 1
				if (d == 0) d = -1;
				float y = (rand() % 10) * d;
				
				Vec2 lastdir{ x,y };
				D3DXVec2Normalize(&lastdir, &lastdir);
				BulletManager::GetInstance().Spawn(pos, lastdir , B_NAVALGUNBULLET);
				--currentBullet;
			}
		}

		for (auto iter : dirs)
		{
			if (currentBullet <= 0)
				break;

			float length = D3DXVec2Length(&iter);
			if (length > 340.f)
				continue;
			BulletManager::GetInstance().Spawn(pos, iter, B_NAVALGUNBULLET);
			--currentBullet;
		}
		shootdelay = 0.5f;
	}

	reloadtime -= Time::dt;
	if (reloadtime < 0)
	{
		reloadtime = 1.f;
		currentBullet += 1;
		if (currentBullet > 5)
			currentBullet = 5;
	}
}

TorpedoLauncher::TorpedoLauncher()
{
}

void TorpedoLauncher::Shoot(Vec2 pos)
{
	//BulletManager::GetInstance().Spawn(pos, dir, B_TORPEDO);
}

MissileLauncher::MissileLauncher()
{
}

void MissileLauncher::Shoot(Vec2 pos)
{
	//BulletManager::GetInstance().Spawn(pos, dir, B_MISSILE);
}

std::vector<Vec2> Weapon::CheckShoot(Vec2 pos)
{
	std::vector<Vec2> finalv;
	float currentMinLength = 99999.f;
	for (auto iter : ObsticleManager::GetInstance().o)
	{
		if (iter->isactive == false)
			continue;

		Vec2 dist = iter->position - pos;
		float length = D3DXVec2Length(&dist);
		if (length < currentMinLength)
		{
			currentMinLength = length;
			finalv.push_back(dist);
		}
	}
	return finalv;
}
