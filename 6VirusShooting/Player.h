#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
    float invincibleTime = 0.f;
    float speedbuffTime = 0.f;

    Player();

    void Damaged(int damage) override;

    void Move();
    void Action() override;
};

