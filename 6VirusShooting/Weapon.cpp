#include "DXUT.h"
#include "Bullet.h"
#include "Obsticle.h"
#include "Monster.h"
#include "Weapon.h"

MachineGun::MachineGun()
{
	currentBullet = 30;
	shootdelay = 0.2f;
	reloadtime = 5.f;
	autoReload = true;
}

void MachineGun::Shoot(Vec2 pos)
{
	shootdelay -= Time::dt;
	focustime -= Time::dt;
	std::cout << currentBullet << std::endl;
	if (DXUTIsKeyDown(VK_SPACE))
	{
		if (shootdelay < 0 && currentBullet > 0)
		{
			std::vector<Vec2> dirs = CheckShoot(pos, this).dirs;
			if (dirs.size() > 0)
			{
				Vec2 lastdir;
				D3DXVec2Normalize(&lastdir, &dirs[dirs.size() - 1]);
				BulletManager::GetInstance().Spawn(pos, lastdir, B_MACHINEGUNBULLET);

				if (focustime > 0)
					shootdelay = 0.05f;
				else
				{
					shootdelay = 0.2f;
					--currentBullet;
				}
			}
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
	reloadtime -= Time::dt;

	if (DXUTWasKeyPressed(VK_SPACE))
	{
		if (shootdelay < 0)
		{
			std::vector<Vec2> dirs = CheckShoot(pos, this).dirs;
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
					BulletManager::GetInstance().Spawn(pos, lastdir, B_NAVALGUNBULLET, nullptr, 5);
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
	}
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
	currentBullet = 5;
	shootdelay = 0.5f;
}

void TorpedoLauncher::Shoot(Vec2 pos)
{
	shootdelay -= Time::dt;
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		if (shootdelay < 0 && currentBullet > 0)
		{
			Sprite* sp = CheckShoot(pos, this).sp;
			if (sp != nullptr)
			{
				BulletManager::GetInstance().Spawn(pos, Vec2(0, 0), B_TORPEDO, &sp->position, 10);
				shootdelay = 0.5f;
				--currentBullet;
			}
		}
	}
}

MissileLauncher::MissileLauncher()
{
	currentBullet = 5;
	shootdelay = 0.5f;
}

void MissileLauncher::Shoot(Vec2 pos)
{
	shootdelay -= Time::dt;
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		if (shootdelay < 0 && currentBullet > 0)
		{
			Sprite* sp = CheckShoot(pos, this).sp;
			if (sp != nullptr)
			{
				BulletManager::GetInstance().Spawn(pos, Vec2(0, 0), B_MISSILE, &sp->position, 10);
				shootdelay = 0.5f;
				--currentBullet;
			}
		}
	}
}

ReturnData Weapon::CheckShoot(Vec2 pos, Weapon* thisw)
{
	ReturnData data;
	std::vector<Vec2> finalv;
	float currentMinLength = 99999.f;

	MissileLauncher* m = dynamic_cast<MissileLauncher*>(thisw);
	TorpedoLauncher* t = dynamic_cast<TorpedoLauncher*>(thisw);

	if (m == nullptr)
	{
		for (auto iter : ObsticleManager::GetInstance().o)
		{
			if (iter->isactive == false)
				continue;

			Vec2 dist = iter->position - pos;
			float length = D3DXVec2Length(&dist);
			if (length < currentMinLength)
			{
				currentMinLength = length;
				data.sp = iter;
				finalv.push_back(dist);
			}
		}
	}

	for (auto iter : MonsterManager::GetInstance().m)
	{
		if (iter->isactive == false)
			continue;
		if (iter->isdead == true)
			continue;

		if (m != nullptr && iter->type == M_SEAMONSTER)
			continue;

		if (t != nullptr && iter->type == M_SKYMONSTER)
			continue;

		Vec2 dist = iter->position - pos;
		float length = D3DXVec2Length(&dist);
		if (length < currentMinLength)
		{
			currentMinLength = length;
			data.sp = iter;
			finalv.push_back(dist);
		}
	}

	data.dirs = finalv;
	return data;
}
