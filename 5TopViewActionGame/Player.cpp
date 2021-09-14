#include "DXUT.h"
#include "Item.h"
#include "Camera.h"
#include "Bullet.h"
#include "Player.h"

Player::Player() : upAttack(strValue + 1)
{
	movespeed = 300;
	hp = maxHP;
	layer = 100;
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

		std::pair<Vec4, std::vector<Vec2>> temp;

		temp.first.x = 0.5f;
		temp.first.y = strValue;
		temp.first.z = 0;
		temp.first.w = 1;

		temp.second.push_back(Vec2(p.x, p.y));
		bulletqueue.push(temp);

		dontmoveTime = 0.4f;
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
				std::pair<Vec4, std::vector<Vec2>> temp;
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
					temp.first.x = 0.2f;
					temp.first.y = strValue + 2;
					temp.first.z = 1;
					temp.first.w = 0;
					// ������ 3���� �Ѿ��� 3��
					temp.second.push_back(-dir);
				}
				bulletqueue.push(temp);
			}
			attackgauge = 0;
			dontmoveTime = 0.5f;
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
			std::pair<Vec4, std::vector<Vec2>> temp;
			// ���� ��� �ð� ������
			temp.first.x = 0.1f;
			temp.first.y = strValue + 1; 
			temp.first.z = 0;
			temp.first.w = 1;
			// ������ 3���� �Ѿ��� 3��
			temp.second.push_back(Vec2(p.x, p.y));
			bulletqueue.push(temp);
		}
		attackspeed = 1.2f;
		dontmoveTime = 0.8f;
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
				std::pair<Vec4, std::vector<Vec2>> temp;
				// ���� ��� �ð� ������
				temp.first.x = 0.1f;
				temp.first.y = strValue + 1;
				temp.first.z = 0;
				temp.first.w = 0;
				// ������ 3���� �Ѿ��� 3��
				temp.second.push_back(Vec2(p.x, p.y));
				aimPos = Vec2(p.x, p.y);
				bulletqueue.push(temp);
			}
			aimTime = 1.f;
			attackgauge = 0;
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
			std::pair<Vec4, std::vector<Vec2>> temp = bulletqueue.front();
			spawnTime = temp.first.x;

			for (auto iter : temp.second)
			{
				BManager::GetInstance().Spawn(position, iter, temp.first.y, temp.first.z, temp.first.w);
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

	if (hpuigauge == 4)
	{
		Heal(maxHP);
		hpuigauge = 0;
	}

	if (aimTime < 0)
		aimPos = { -999, -999 };
	else
		aimTime -= DXUTGetElapsedTime();

	if (DXUTWasKeyPressed('B'))
		Damaged(1);

	CollideItem();
	CheckAttackUp();
	Move();
	Shoot();
}