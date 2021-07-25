#pragma once
#include "Monster.h"
class Octopus final :
    public Monster
{

public:
    explicit Octopus(Player* p);
    virtual ~Octopus();
    void Damaged() override { std::cout << "È£¾Þ¾Þ" << std::endl; };

    void Action() override;
};