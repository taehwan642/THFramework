#include "DXUT.h"
#include "TileMapManager.h"
#include "GameObject.h"

void GameObject::Heal(int healvalue)
{
	hp += healvalue;
	if (hp > maxHP)
	{
		hp = maxHP;
	}
}

void GameObject::Damaged(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		// Á×¾ú´ç
		
	}
}

bool GameObject::Collide()
{
	TileMapManager& tm = TileMapManager::GetInstance();

	bool col = false;

	for (auto iter : tm.tileBlocks)
	{
		if (iter->type == FLOOR)
			continue;
		RECT r;
		if (IntersectRect(&r, &GetRect(), &iter->GetRect()))
		{
			col = true;
			float xlength = r.right - r.left;
			float ylength = r.bottom - r.top;

			if (xlength < ylength)
			{
				// x
				float mypivot = (GetRect().right + GetRect().left) / 2;
				float iterpivot = (iter->GetRect().right + iter->GetRect().left) / 2;
				if (mypivot < iterpivot)
					// ¿ÞÂÊ
					position.x -= xlength;
				else
					position.x += xlength;
			}
			else
			{
				// y
				float mypivot = (GetRect().bottom + GetRect().top) / 2;
				float iterpivot = (iter->GetRect().bottom + iter->GetRect().top) / 2;
				if (mypivot < iterpivot)
					// ¿ÞÂÊ
					position.y -= ylength;
				else
					position.y += ylength;
			}
		}
	}

	for (auto iter : tm.objBlocks)
	{
		RECT r;
		if (IntersectRect(&r, &GetRect(), &iter->GetRect()))
		{
			col = true;
			float xlength = r.right - r.left;
			float ylength = r.bottom - r.top;

			if (xlength < ylength)
			{
				// x
				float mypivot = (GetRect().right + GetRect().left) / 2;
				float iterpivot = (iter->GetRect().right + iter->GetRect().left) / 2;
				if (mypivot < iterpivot)
					// ¿ÞÂÊ
					position.x -= xlength;
				else
					position.x += xlength;
			}
			else
			{
				// y
				float mypivot = (GetRect().bottom + GetRect().top) / 2;
				float iterpivot = (iter->GetRect().bottom + iter->GetRect().top) / 2;
				if (mypivot < iterpivot)
					// ¿ÞÂÊ
					position.y -= ylength;
				else
					position.y += ylength;
			}
		}
	}
	return col;
}

void GameObject::Update()
{
	attackspeed -= DXUTGetElapsedTime();
	dontmoveTime -= DXUTGetElapsedTime();

	Action();

	isCollide = Collide();
}
