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
			// ���⺤�� ���ϱ�
			float dirX = iter->position.x - position.x;
			float dirY = iter->position.y - position.y;
			Vec2 d = { dirX, dirY };
			// ũ�� 1�� ����
			D3DXVec2Normalize(&d, &d);
			// (���⺤�� ��������) ������ �����ֱ�
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
	// auto iter
	// Monster* iter
	// monsters �ȿ� �ִ� �������� �ּ�
	// auto iter�� ������� �������� �ּҴ� ���� �ʾƿ�
	// Monster* iter, Monster* a;
	// alias
	
	// �� ó�� ���ư��� ��
	// iter�� monsters[0]�� ������ �ּҴ� ����? Ʋ����
	// iter�� monsters[0]�� ����Ű�� �ִ� �ּҴ� ����? ���ƿ�
	
	// Monsters* a = new Monsters;
	// Monsters* iter = a;
	// ������ �ּҴ� �ٸ����� ���� ���� �����ִ�

	// delete iter;

	// iter = new Monsters;
	// a �ٸ� �����ϱ�

	// &�̰� ���̸� monsters[0]�� iter�� ������ �ּҴ� ����
	// �ٶ󺸰��ִ°͵� ����. ���Ф�? �ּҰŤ� �����ϱ�.
	// 
	for (auto& iter : monsters)
	{
		// �� �ڵ��� ����
		// �������Ͱ� �ƴϴ�? �׷� �ϴ� ����ִٴ� ����?
		// �ٵ� �������Ͱ� �ƴϸ鼭 isactive == true
		// �׷��� ������ �ʿ� ���δٴ°ǵ� �װ� delete�� ���� ����?
		if (nullptr != iter && true == iter->isactive) // �ʿ� ���δ�.
		{
			// �� ���͸� �ǵ帮�� �ʴ´�.
			continue;
		}

		// isactive�� false�ų� nullptr�� �� �����´�.
		if (iter != nullptr)
		{
			// delete
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
	// auto&�� �ƴϾ �Ǵ� ����
	// �������� �ּҴ� ���� �ʾƵ�
	// �����Ͱ� �ٶ󺸴� �ּҴ� ����?
	for (auto iter : monsters)
	{
		if (iter != nullptr)
			delete iter;
	}
	monsters.clear();
}
