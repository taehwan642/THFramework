#include "DXUT.h"
#include "Item.h"
#include "Camera.h"
#include "Bullet.h"
#include "Effect.h"
#include "Player.h"

Player::Player() : upAttack(strValue + 1)
{
	movespeed = 300;
	hp = maxHP;
	layer = 100;
	
	CreateAnimation(L"player", 6, 0.3f); // idle
	CreateAnimation(L"playershoot", 3, 0.1f); // 약공격, 강공격 & 루시안궁
	CreateAnimation(L"playershotgun", 3, 0.1f);
	CreateAnimation(L"lucian/lucian", 15, 0.1f);
	PlayAnimation(L"player");
}

void Player::HpUIUp(int healvalue)
{
	hpuigauge += healvalue;
	if (hpuigauge > 4)
	{
		hpuigauge = 4;
	}
}

void Player::CollideItem()
{
	for (auto iter : ItemManager::GetInstance().items)
	{
		if (false == iter->isactive)
			continue;
		RECT r;
		if (IntersectRect(&r, &GetRect(), &iter->GetRect()))
		{
			// 부딪혔다! 그 머냐 그거 그 그 이펙트 활성화
			iter->Effect(this); //<- 아이템의 고유 이펙트
		}
	}
}

void Player::CheckAttackUp()
{
	attackupTick -= DXUTGetElapsedTime();

	if (attackupTick > 0)
	{
		strValue = upAttack;
	}
	else
	{
		strValue = upAttack - 1;
	}
}

void Player::Move()
{
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	Camera& cam = Camera::GetInstance();
	Vec2 camPos = cam.GetPosition();
	p.x = (camPos.x - screenwidth / 2) + p.x;
	p.y = (camPos.y - screenheight / 2) + p.y;

	Lookat(Vec2(p.x, p.y));

	if (dontmoveTime > 0)
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

bool Player::WeakShoot()
{
	if (attackspeed < 0)
	{
		attackspeed = 0.5f;

		ShootData temp;

		temp.spawntime = 0.5f;
		temp.damage = strValue;
		temp.spawntype = 0;
		temp.isweak = 1;

		temp.dir.push_back(Vec2(p.x, p.y));
		bulletqueue.push(temp);

		dontmoveTime = 0.4f;
		state = SHOOT;
	}
	return true;
}

bool Player::SpecialWeakShoot()
{
	if (DXUTIsKeyDown('W'))
	{
		if (attackgauge == 10)
		{
			for (int i = 0; i < 2; ++i)
			{
				ShootData temp;
				for (int r = -30; r <= 30; r += 30)
				{
					Vec2 dir;
					// degree? radian?

					// 지금 현재 r만 쓰면 고정각.

					// r degree
					// 플레이어가 사용하는 rotation == radian
					float protplusr = r + D3DXToDegree(rotation);

					dir.x = cos(D3DXToRadian(protplusr));
					dir.y = sin(D3DXToRadian(protplusr));
					// cos == x
					// sin == y

					// 다음 쏘는 시간 딜레이
					temp.spawntime = 0.2f;
					temp.damage = strValue + 2;
					temp.spawntype = 1;
					temp.isweak = 0;
					// 방향이 3개면 총알은 3개
					temp.dir.push_back(-dir);
				}
				bulletqueue.push(temp);
			}
			attackgauge = 0;
			dontmoveTime = 0.5f;
			attackspeed = 0.2f; 
			// 위치에서 바라보는 방향으로 약간 더 움직여야 총구쪽으로 향한다.
			// position + dir * scalar (float)

			// 방향벡터 구하기
			float dirX = p.x - position.x;
			float dirY = p.y - position.y;
			Vec2 d = { dirX, dirY };
			// 크기 1로 세팅
			D3DXVec2Normalize(&d, &d);
			// (방향벡터 방향으로) 앞으로 땡겨주기
			Vec2 res =
			{
				position.x + d.x * 80,
				position.y + d.y * 80
			};
			// 스폰
			EManager::GetInstance().Spawn(res, E_SHOTGUN, rotation);
			state = SHOTGUN;
			return true;
		}
	}
	return false;
}

bool Player::StrongShoot()
{
	if (attackspeed < 0)
	{
		for (int i = 0; i < 3; ++i)
		{
			ShootData temp;
			// 다음 쏘는 시간 딜레이
			temp.spawntime = 0.1f;
			temp.damage = strValue + 1; 
			temp.spawntype = 0;
			temp.isweak = 1;
			// 방향이 3개면 총알은 3개
			temp.dir.push_back(Vec2(p.x, p.y));
			bulletqueue.push(temp);
		}
		attackspeed = 1.2f;
		dontmoveTime = 0.5f;
		state = SHOOT;
		return true;
	}
	return false;
}

bool Player::SpecialStrongShoot()
{
	if (DXUTIsKeyDown('W') && DXUTIsKeyDown('S'))
	{
		if (attackgauge >= 10)
		{
			for (int i = 0; i < 10; ++i)
			{
				ShootData temp;
				// 다음 쏘는 시간 딜레이
				temp.spawntime = 0.1f;
				temp.damage = strValue + 1;
				temp.spawntype = 0;
				temp.isweak = 0;
				// 방향이 3개면 총알은 3개
				temp.dir.push_back(Vec2(p.x, p.y));
				aimPos = Vec2(p.x, p.y);
				bulletqueue.push(temp);
			}
			aimTime = 1.f;
			attackgauge = 0;
			attackspeed = 0.2f;
			state = LUCIAN;
			return true;
		}
	}
	
	return false;
}

void Player::Shoot()
{
	if (spawnTime < 0)
	{
		if (bulletqueue.size() > 0)
		{
			ShootData temp = bulletqueue.front();
			spawnTime = temp.spawntime;

			for (auto iter : temp.dir)
			{
				BManager::GetInstance().Spawn(position, iter, temp.damage, temp.spawntype, temp.isweak);
			}
			bulletqueue.pop();
		}
	}
	else
		spawnTime -= DXUTGetElapsedTime();

	// 0 왼쪽 1 마우스 휠 2 오른쪽
	if (DXUTIsMouseButtonDown(0))
	{
		// specialWeakShoot 검사
		// 쏠 수 있다면 true
		// 쏠 수 없다면 false
		if (!SpecialWeakShoot())
		{
			WeakShoot();
		}
	}
	else if (DXUTIsMouseButtonDown(2))
	{
		if (!SpecialStrongShoot())
		{
			StrongShoot();
		}
	}
}

void Player::Action()
{
	if (isdead == true)
		return;
	hp = 5;
	switch (state)
	{
	case IDLE:
		PlayAnimation(L"player");
		break;
	case SHOOT:
		if(PlayAnimation(L"playershoot"))
			state = IDLE;
		break;
	case SHOTGUN:
		if(PlayAnimation(L"playershotgun"))
			state = IDLE;
		break;
	case LUCIAN:
		if (PlayAnimation(L"lucian/lucian"))
			state = IDLE;
		break;
	default:
		break;
	}
	// 만약 쏘고있지 않을 때
	// idle 애니메이션 실행
	// 만약 쏘고있을 때
	// shoot 애니메이션 실행

	if (DXUTWasKeyPressed('H'))
	{
		if (hpuigauge == 4)
		{
			EManager::GetInstance().Spawn(position, E_HEAL);
			Heal(maxHP);
			hpuigauge = 0;
		}
	}


	if (aimTime < 0)
		aimPos = { -999, -999 };
	else
		aimTime -= DXUTGetElapsedTime();

	/*if (DXUTWasKeyPressed('B'))
		Damaged(1);*/

	CollideItem();
	CheckAttackUp();
	Move();
	Shoot();
}