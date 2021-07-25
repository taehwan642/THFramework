#pragma once
#include "GameObject.h"
class Monster :
    public GameObject
{
public:
    Player* player;
    explicit Monster(Player* p) : player(p) {};
    virtual ~Monster();

    void Damaged() override {};

    void Action() override;
};