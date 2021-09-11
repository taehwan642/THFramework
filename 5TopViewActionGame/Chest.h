#pragma once
#include "AniSprite.h"
class Chest :
    public AniSprite
{
    // (충돌)맞는거
    // 텍스처 바꾸는 기능
    // hp
    int hp = 0;
    // 아이템 뿌리는 기능
public:
    Chest();
    void ItemSpawn();
    void Collide();
    void Update() override;
};

