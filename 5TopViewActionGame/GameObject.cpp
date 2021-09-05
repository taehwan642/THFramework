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
		// �׾���
		
	}
}

void GameObject::Update()
{
	// �浹ó��

	

	// ������ó��
	// ���..
	Action();
}
