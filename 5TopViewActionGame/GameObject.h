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

    int strValue = 1; // 공격력

    float movespeed = 100.f;

    void Heal(int healvalue); // 즉시 회복
    void Damaged(int damage);

    virtual void Action() PURE;
    void Update() override;
};

