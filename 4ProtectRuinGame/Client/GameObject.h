#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
protected:
    bool gravity;
    bool isonfloor;

    Sprite* collider;

    explicit GameObject();

    StateManager* stm;

    friend class IdleState;
    friend class RunState;
    friend class AttackState;
    friend class JumpState;
    friend class JumpEndState;

public:
    virtual ~GameObject();

    void CheckCollision();

    virtual void Action() PURE;

    void Update() override;
};

