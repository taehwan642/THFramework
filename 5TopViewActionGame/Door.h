#pragma once
#include "Sprite.h"
class Door :
    public Sprite
{
public:
    Door();

    int currentDoorTexture = 0;
    int currentDoorIndex = 1;
    bool isOpen = false;
    std::wstring SetDoorTexture(int doorIndex);
    void CheckOpen();
    bool CollisionPlayer(Vec2 pos);
    void Update() override;
};

