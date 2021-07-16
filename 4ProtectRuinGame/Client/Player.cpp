#include "DXUT.h"
#include "TileMapManager.h"
#include "Player.h"

Player::Player() :
	gravity(true),
	velocity(0, 0),
	isonfloor(false)
{
	statechanger = new IdleState(this);
	CreateAnimation(L"run", 6, 0.1f);
	CreateAnimation(L"attack", 3, 0.1f);
	CreateAnimation(L"idle", 2, 0.6f);
	CreateAnimation(L"jump", 3, 0.15f);
	PlayAnimation(L"idle");

	collider = new Sprite();
	collider->SetTexture(L"box.png");

}

Player::~Player()
{
	delete statechanger;
	delete collider;
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
				{
					isonfloor = true;
					position.y -= result.bottom;
				}
				else
					position.y += result.bottom;
			}
			else
			{
				if ((myRect.right + myRect.left) / 2 <= (boxRect.right + boxRect.left) / 2)
				{
					position.x -= result.right;
				}
				else
				{
					// 충돌처리 계산의 치명적인 부분을 손봐줄 야매 코드.
					if (result.bottom > 20)
						position.x += result.right;
				}
			}
		}
	}
}

void
Player::Update()
{
	if (gravity == true)
		position.y += 1000.f * DXUTGetElapsedTime();

	CheckCollision();
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
		case PlayerStates::JUMP:
			statechanger = new JumpState(this);
			break;
		default:
			break;
		}
		currentstate = ps;
	}
	collider->position = position;
}
