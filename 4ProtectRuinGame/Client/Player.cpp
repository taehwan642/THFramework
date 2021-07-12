#include "DXUT.h"
#include "TileMapManager.h"
#include "Player.h"

Player::Player()
{
	statechanger = new IdleState(this);
	CreateAnimation(L"run", 6, 0.1f);
	CreateAnimation(L"attack", 3, 0.1f);
	CreateAnimation(L"idle", 2, 0.6f);
	PlayAnimation(L"idle");
}

Player::~Player()
{
	delete statechanger;
}

void 
Player::CheckCollision()
{
	std::vector<Block> v = TileMapManager::GetInstance().GetBlockVector();
	
	for (const auto& iter : v)
	{
		Sprite* bs = iter.sprite;
		RECT result;
		RECT boxRect = bs->GetRect();
		RECT myRect = GetRect();
		if (IntersectRect(&result, &myRect, &boxRect))
		{
			SetRect(&result, 0, 0, result.right - result.left, result.bottom - result.top);
			if (result.right > result.bottom)
			{
				if ((myRect.bottom + myRect.top) / 2 < (boxRect.bottom + boxRect.top) / 2)
					position.y -= result.bottom;
				else
					position.y += result.bottom;
			}
			else
			{
				if ((myRect.right + myRect.left) / 2 < (boxRect.right + boxRect.left) / 2)
					position.x -= result.right;
				else
					position.x += result.right;
			}
		}
	}
}

void 
Player::Update()
{
	PlayerStates ps = statechanger->handleInput();
	if (ps != currentstate)
	{
		delete statechanger;
		switch (ps)
		{
		case PlayerStates::IDLE:
			statechanger = new IdleState(this);
			break;
		case PlayerStates::RUN:
			statechanger = new RunState(this);
			break;
		case PlayerStates::ATTACK:
			statechanger = new AttackState(this);
			break;
		default:
			break;
		}
		currentstate = ps;
	}
	CheckCollision();
}
