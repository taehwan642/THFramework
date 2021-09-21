#include "DXUT.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"

Monster::Monster()
{
	hpui = new Sprite;
	hpuibar = new Sprite;
	hpuibar->SetTexture(L"mhpbar.png");
	hpui->layer = 200;
	hpuibar->layer = 199;
}

Monster::~Monster()
{
	delete hpui;
	delete hpuibar;
}

void Monster::CollideBullet()
{
	for (auto iter : BManager::GetInstance().bullets)
	{
		if (iter->isactive == false)
			continue;
		Vec2 dist = iter->position - position;
		float length = D3DXVec2Length(&dist);

		if (length < 40.f)
		{
			Damaged(iter->strValue);
			// 방향벡터 구하기
			float dirX = iter->position.x - position.x;
			float dirY = iter->position.y - position.y;
			Vec2 d = { dirX, dirY };
			// 크기 1로 세팅
			D3DXVec2Normalize(&d, &d);
			// (방향벡터 방향으로) 앞으로 땡겨주기
			Vec2 res =
			{
				position.x - d.x * 30,
				position.y - d.y * 30
			};

			position = res;
			iter->isactive = false;
		}

	}
}

void Monster::HPUIUpdate()
{
	Vec2 uiPos = { position.x, position.y - 80 };
	hpui->position = uiPos;
	hpuibar->position = uiPos;

	float x = (float)hpuibar->GetTexture()->info.Width * ((float)hp / (float)maxHP);
	SetRect(&hpuibar->imgRect, 0, 0, (int)x, hpuibar->GetTexture()->info.Height);
}

void Monster::Action()
{
	if (isdead == true)
	{
		isactive = false;
	}
	Lookat(player->position);

	CollideBullet();
	HPUIUpdate();
	Follow();
	Attack();

	switch (state)
	{
	case M_IDLE:
		IdleState();
		break;
	case M_ATTACK:
		if (AttackState())
		{
			state = M_IDLE;
		}
		break;
	default:
		break;
	}
}
