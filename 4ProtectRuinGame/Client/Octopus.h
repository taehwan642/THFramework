#pragma once
#include "Monster.h"
class Octopus final :
    public Monster
{

public:
    explicit Octopus(Player* p);
    virtual ~Octopus();

    void Action() override;
};