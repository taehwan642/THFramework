#pragma once
#include "Monster.h"
class Octopus :
    public Monster
{
public:
    explicit Octopus();
    virtual ~Octopus();

    void Action() override;
};