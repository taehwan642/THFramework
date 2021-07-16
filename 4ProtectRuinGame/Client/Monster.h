#pragma once
#include "AniSprite.h"
class Monster :
    public AniSprite
{
public:
    explicit Monster();
    virtual ~Monster();

    void Update() override;
};