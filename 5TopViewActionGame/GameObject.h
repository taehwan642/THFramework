#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
public:
    virtual ~GameObject() {};

    bool isAttacking = false;

    int hp = 5;
    float movespeed = 100.f;

    virtual void Action() PURE;
    void Update() override;
};

