#pragma once
#include "PlayerState.h"
#include "Sprite.h"
class Player final :
    public Sprite
{
    PlayerState* statechanger;
    PlayerStates currentstate;

public:
    explicit Player();
    virtual ~Player();
    void Update() override;
};

