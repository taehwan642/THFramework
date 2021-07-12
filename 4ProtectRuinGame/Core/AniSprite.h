#pragma once
#include "Sprite.h"
class AniSprite :
    public Sprite
{
private:
    std::wstring currentAnimationTag;
    float delta;

public:
    bool Animation();
};

