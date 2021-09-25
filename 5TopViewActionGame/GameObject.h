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

    int strValue = 1; // 공격력

    float movespeed = 100.f;

    float attackspeed = 0.0f;

    bool isCollide = false;

    bool isdead = false;
    virtual void Dead() {}; // 죽었을 때 나오는 효과

    void Heal(int healvalue); // 즉시 회복
    virtual void Damaged(int damage);

    bool Collide();

    virtual void Action() PURE;
    void Update() override;
};

