#pragma once
#include "AniSprite.h"
class Player final :
    public AniSprite
{
private:
    PlayerState* statechanger;
    PlayerStates currentstate;

    Sprite* collider;

public:
    explicit Player();
    virtual ~Player();

    void CheckCollision();

    void Update() override;
};

