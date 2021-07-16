#pragma once
#include "AniSprite.h"
class Player final :
    public AniSprite
{
private:
    bool gravity;
    bool isonfloor;

    PlayerState* statechanger;
    PlayerStates currentstate;

    Sprite* collider;

    friend class IdleState;
    friend class RunState;
    friend class AttackState;
    friend class JumpState;
    friend class JumpEndState;

public:
    explicit Player();
    virtual ~Player();

    void CheckCollision();

    void Update() override;
};

