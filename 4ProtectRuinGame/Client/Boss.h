#pragma once
#include "Monster.h"
class Boss :
    public Monster
{
public:
    explicit Boss(Player* p);
    virtual ~Boss();

    void Action() override;
};