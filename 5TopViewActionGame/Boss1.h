#pragma once
#include "Monster.h"
class Boss1 :
    public Monster
{
public:
    int pattern = 0;
    Boss1();
    virtual ~Boss1();
    void Dead() override;
    void Follow() override;
    void CheckCanAttack() override;
    void SetStat(int diff) override;
    bool IdleState() override;
    bool AttackState() override;
};
