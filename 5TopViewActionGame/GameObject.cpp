#include "DXUT.h"
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
		// 죽었당
		
	}
}

void GameObject::Update()
{
	// 충돌처리

	

	// 움직임처리
	// 등등..
	Action();
}
