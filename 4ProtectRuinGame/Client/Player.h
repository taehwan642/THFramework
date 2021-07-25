#pragma once
#include "GameObject.h"

class Player final :
    public GameObject
{
private:

public:
    explicit Player();
    virtual ~Player();

    void Action() override;

    void Damaged() override;
};

