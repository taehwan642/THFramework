#include "DXUT.h"
#include "TileMapManager.h"
#include "GameObject.h"

GameObject::GameObject() :
	gravity(true),
	isonfloor(false),
	HP(5),
	moveSpeed(1),
	barrierCount(0),
	level(1),
	exp(0),
	attackLevel(1),
	attackSpeed(1),
	lookingRight(true),
	wallcollided(false)
{
	collider = new Sprite();
	collider->SetTexture(L"box.png");

	stm = new StateManager;
	
}

GameObject::~GameObject()
{
	delete collider;
	stm->DeleteStates();
	delete stm;
}

void 
GameObject::CheckCollision()
{
	std::vector<Block> v = TileMapManager::GetInstance().GetBlockVector();
	wallcollided = false;
	for (const auto& iter : v)
	{
		Sprite* bs = iter.sprite;
		RECT result;
		RECT boxRect = bs->GetRect();
		RECT myRect = collider->GetRect();
		if (IntersectRect(&result, &myRect, &boxRect))
		{
			SetRect(&result, 0, 0, result.right - result.left, result.bottom - result.top);
			if (result.right > result.bottom)
			{
				if ((myRect.bottom + myRect.top) / 2 < (boxRect.bottom + boxRect.top) / 2)
				{
					isonfloor = true;
					collider->position.y -= result.bottom;
				}
				else
					collider->position.y += result.bottom;
			}
			else
			{
				bool col = false;
				if ((myRect.right + myRect.left) / 2 <= (boxRect.right + boxRect.left) / 2)
				{
					collider->position.x -= result.right;
					col = true;
				}
				else
				{
					// 충돌처리 계산의 치명적인 부분을 손봐줄 야매 코드.
					if (result.bottom > 40)
					{
						collider->position.x += result.right;
						col = true;
					}
				}
				wallcollided = col;
			}
		}
	}
}


void
GameObject::Update()
{
	if (false == isactive)
		return;

	if (gravity == true)
	{
		collider->position.y += 1500.f * DXUTGetElapsedTime();
		if (collider->position.y > 1408.f)
		{
			collider->position.y = 1408.f;
			isonfloor = true;
		}
	}

	CheckCollision();

	Action();

	stm->UpdateState();

	position = collider->position;
}

void GameObject::GetAttack(int damage)
{
	if (false == Check_CanGetAttack())
		return;

	if (barrierCount != 0)
	{
		--barrierCount;
		return;
	}
	HP -= damage;
	Damaged();
}