#pragma once
#include "AniSprite.h"
class Player final :
    public AniSprite
{
private:
    PlayerState* statechanger;
    PlayerStates currentstate;

public:
    explicit Player();
    virtual ~Player();

    void CheckCollision();

    void Update() override;
};

