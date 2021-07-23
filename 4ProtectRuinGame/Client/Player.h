#pragma once
#include "GameObject.h"

class Player final :
    public GameObject
{
private:
    friend class IdleState;
    friend class RunState;
    friend class AttackState;
    friend class JumpState;
    friend class JumpEndState;

public:
    explicit Player();
    virtual ~Player();

    void Action() override;
};

