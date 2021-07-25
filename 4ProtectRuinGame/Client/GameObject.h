#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
protected:
    explicit GameObject();

    StateManager* stm;

    friend class IdleState;
    friend class RunState;
    friend class AttackState;
    friend class JumpState;
    friend class JumpEndState;
    friend class DamagedState;

public:
    bool gravity;
    bool isonfloor;

    int HP;
    float moveSpeed;
    int barrierCount;

    int level;
    int exp;

    int attackLevel;
    float attackSpeed;
    bool lookingRight; // �������� �ٶ󺸰� �ֳ�?

    bool wallcollided;

    Sprite* collider;

    virtual ~GameObject();

    void CheckCollision();

    virtual void Action() PURE;

    __forceinline constexpr void
        SetPosition(const Vec2& pos);

    void GetAttack(int damage);

    virtual void Damaged() PURE;

    void Update() override final;
};

constexpr void 
GameObject::SetPosition(const Vec2& pos)
{
    collider->position = pos;
}