#pragma once
#include "GameObject.h"

class Weapon;

class Player :
    public GameObject
{
public:
    std::vector<Weapon*> weapons;
    int currentWeapon = 0;

    float invincibleTime = 0.f;
    float speedbuffTime = 0.f;
    float speedbuffValue = 0.f;

    // 

    Player();
    virtual ~Player();

    void Collision();

    void Shoot();
    void Damaged(int damage) override;

    void Move();
    void Action() override;
};

