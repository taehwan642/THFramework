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

    int MaxHP;
    int HP;
    float moveSpeed;
    int barrierCount;

    int level;
    int exp;

    int attackLevel;
    float attackSpeed;
    bool lookingRight; // 오른쪽을 바라보고 있냐?

    bool wallcollided;

    bool isDamaged = false;

    Sprite* collider;

    Vec2 pushDirection;

    virtual ~GameObject();

    void CheckCollision();

    virtual void Action() PURE;

    __forceinline constexpr void
        SetPosition(const Vec2& pos);

    virtual bool Check_CanGetAttack() { return true; }

    void GetAttack(int damage, const Vec2& pushDir);

    virtual void Damaged() { isDamaged = true; };

    void Update() override final;
};

constexpr void 
GameObject::SetPosition(const Vec2& pos)
{
    collider->position = pos;
}