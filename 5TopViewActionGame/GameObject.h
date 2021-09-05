#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
public:
    virtual ~GameObject() {};

    bool isAttacking = false;

    int hp = 5;
    int maxHP = 5;

    int strValue = 1; // ���ݷ�

    float movespeed = 100.f;

    void Heal(int healvalue); // ��� ȸ��
    void Damaged(int damage);

    virtual void Action() PURE;
    void Update() override;
};

