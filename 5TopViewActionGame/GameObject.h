#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
public:
    virtual ~GameObject() {};

    float dontmoveTime = 0.0f;

    int hp = 5;
    int maxHP = 5;

    int strValue = 1; // ���ݷ�

    float movespeed = 100.f;

    float attackspeed = 0.0f;

    bool isCollide = false;

    bool isdead = false;
    virtual void Dead() {}; // �׾��� �� ������ ȿ��

    void Heal(int healvalue); // ��� ȸ��
    virtual void Damaged(int damage);

    bool Collide();

    virtual void Action() PURE;
    void Update() override;
};

