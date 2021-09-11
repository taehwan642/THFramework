#include "DXUT.h"
#include "Item.h"
#include "Camera.h"
#include "Bullet.h"
#include "Player.h"

Player::Player() : upAttack(strValue + 1)
{
	movespeed = 300;
	hp = maxHP;
	keys.push_back(new HealKey(this));
	keys.push_back(new WeakAttackKey(this));
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

void Player::Shoot()
{
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		BManager::GetInstance().Spawn(position, Vec2(p.x, p.y), strValue);
	}
}

void Player::CheckSkillKey()
{
	for (auto iter : keys)
	{
		if (iter->CheckSkill())
		{
			iter->DoSomething();
		}
	}
}

void Player::Action()
{
	CollideItem();
	CheckAttackUp();
	CheckSkillKey();
	Move();
	Shoot();
}

bool SkillKey::CheckSkill()
{
	for (auto iter : sk)
	{
		if (!DXUTIsKeyDown(iter))
		{
			return false;
		}
	}
	return true;
}

void HealKey::DoSomething()
{
	p->Heal(p->maxHP);
	p->hpuigauge = 0;
}

void WeakAttackKey::DoSomething()
{
	std::cout << "오 이게 돼?" << std::endl;
}
