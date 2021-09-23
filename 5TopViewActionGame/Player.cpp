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
	CreateAnimation(L"playershoot", 3, 0.1f); // �����, ������ & ��þȱ�
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
			// �ε�����! �� �ӳ� �װ� �� �� ����Ʈ Ȱ��ȭ
			iter->Effect(this); //<- �������� ���� ����Ʈ
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

					// ���� ���� r�� ���� ������.

					// r degree
					// �÷��̾ ����ϴ� rotation == radian
					float protplusr = r + D3DXToDegree(rotation);

					dir.x = cos(D3DXToRadian(protplusr));
					dir.y = sin(D3DXToRadian(protplusr));
					// cos == x
					// sin == y

					// ���� ��� �ð� ������
					temp.spawntime = 0.2f;
					temp.damage = strValue + 2;
					temp.spawntype = 1;
					temp.isweak = 0;
					// ������ 3���� �Ѿ��� 3��
					temp.dir.push_back(-dir);
				}
				bulletqueue.push(temp);
			}
			attackgauge = 0;
			dontmoveTime = 0.5f;
			attackspeed = 0.2f; 
			// ��ġ���� �ٶ󺸴� �������� �ణ �� �������� �ѱ������� ���Ѵ�.
			// position + dir * scalar (float)

			// ���⺤�� ���ϱ�
			float dirX = p.x - position.x;
			float dirY = p.y - position.y;
			Vec2 d = { dirX, dirY };
			// ũ�� 1�� ����
			D3DXVec2Normalize(&d, &d);
			// (���⺤�� ��������) ������ �����ֱ�
			Vec2 res =
			{
				position.x + d.x * 80,
				position.y + d.y * 80
			};
			// ����
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
			// ���� ��� �ð� ������
			temp.spawntime = 0.1f;
			temp.damage = strValue + 1; 
			temp.spawntype = 0;
			temp.isweak = 1;
			// ������ 3���� �Ѿ��� 3��
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
				// ���� ��� �ð� ������
				temp.spawntime = 0.1f;
				temp.damage = strValue + 1;
				temp.spawntype = 0;
				temp.isweak = 0;
				// ������ 3���� �Ѿ��� 3��
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

	// 0 ���� 1 ���콺 �� 2 ������
	if (DXUTIsMouseButtonDown(0))
	{
		// specialWeakShoot �˻�
		// �� �� �ִٸ� true
		// �� �� ���ٸ� false
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
	// ���� ������� ���� ��
	// idle �ִϸ��̼� ����
	// ���� ������� ��
	// shoot �ִϸ��̼� ����

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