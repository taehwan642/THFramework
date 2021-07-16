#pragma once
#include "AniSprite.h"
class GameObject :
    public AniSprite
{
protected:
    bool gravity;
    bool isonfloor;

    Sprite* collider;

    explicit GameObject();

    StateManager* stm;

public:
    virtual ~GameObject();

    void CheckCollision();

    virtual void Action() PURE;

    void Update() override;
};

