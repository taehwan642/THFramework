#pragma once
#include "Sprite.h"
class VIM :
    public Sprite
{
private:
public:
    int vimscore = 0;


    float movementspeed = 0.07f;
    int HP = 5;
    float immunetime = 0;
    int barriervalue = 0; 

    VIM();
    virtual ~VIM();
    void Update() override;
};

