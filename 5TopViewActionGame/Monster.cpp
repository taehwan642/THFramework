#include "DXUT.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster1.h"
#include "TileMapManager.h"
#include "Monster.h"

Monster::Monster()
{
	hpui = new Sprite;
	hpuibar = new Sprite;
	hpuibar->SetTexture(L"mhpbar.png");
	hpui->layer = 200;
	hpuibar->layer = 199;
	TileMapManager& tm = TileMapManager::GetInstance();
	scale = { tm.blockScale, tm.blockScale };
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
			iter->UpGauge();
			player->score += 20;
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

void MonsterManager::Create()
{
	for (int i = 0; i < 30; ++i)
	{
		Monster* mp = nullptr;
		monsters.push_back(mp);
	}
}

void MonsterManager::Spawn(BlockType type, Vec2 position, int difficulty)
{
	for (auto iter : monsters)
	{
		// 이 코드의 목적
		// 널포인터가 아니다? 그럼 일단 살아있다는 거죠?
		// 근데 널포인터가 아니면서 isactive == true
		// 그러면 무조건 맵에 보인다는건데 그걸 delete할 수는 없죠?
		if (nullptr != iter && true == iter->isactive) // 맵에 보인다.
		{
			// 이 몬스터를 건드리지 않는다.
			continue;
		}

		// isactive가 false거나 nullptr일 때 내려온다.
		if (iter != nullptr)
		{
			delete iter;
			iter = nullptr;
		}

		switch (type)
		{
		case MONSTER1:
			iter = new Monster1;
			break;
		default:
			break;
		}

		iter->SetStat(difficulty);
		iter->player = p;
		iter->position = position;
		
		return;
	}
}

void MonsterManager::Delete()
{
	for (auto iter : monsters)
	{
		if (iter != nullptr)
			delete iter;
	}
	monsters.clear();
}
