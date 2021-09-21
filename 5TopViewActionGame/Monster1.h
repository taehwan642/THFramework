#pragma once
#include "Monster.h"
class Monster1 :
    public Monster
{
public:
    Monster1();
    virtual ~Monster1();
    
    void Dead() override;

    void Follow() override;
    void Attack() override;

    bool IdleState() override;
    bool AttackState() override;
};

