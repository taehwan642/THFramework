#pragma once
#include "GameObject.h"
class Monster :
    public GameObject
{
public:
    Player* player;
    explicit Monster(Player* p) : player(p) {};
    virtual ~Monster();

    static float monstertimeScale;

    __forceinline static float 
        GetDT() { return DXUTGetElapsedTime() * monstertimeScale; };

    float GetDeltaTime() override { return DXUTGetElapsedTime() * monstertimeScale; };

    void Action() override;
};

