#pragma once
#include "GameObject.h"
class Monster :
    public GameObject
{
public:
    explicit Monster();
    virtual ~Monster();

    void Action() override;
};