#pragma once
#include "GameObject.h"

class Player final :
    public GameObject
{
private:
public:
    bool isDodging;
    explicit Player();
    virtual ~Player();

    void Action() override;

    bool Check_CanGetAttack() override;
};

