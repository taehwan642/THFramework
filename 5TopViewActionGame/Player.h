#pragma once
#include "GameObject.h"

#define PLAYERMAXHP 5

class Player :
    public GameObject
{
public:
    int score = 0;

    virtual ~Player() {};

    void Heal(int healvalue);
    Player();
    void Move();
    void Action() override;
};

