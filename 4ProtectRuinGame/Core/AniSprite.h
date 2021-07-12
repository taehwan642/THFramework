#pragma once
#include "Sprite.h"
class AniSprite :
    public Sprite
{
private:
    std::wstring currentAnimationTag;
    std::pair<float, std::vector<Texture*>> currentAnimation;
    int currentFrame;
    float currentTick;

    std::map<std::wstring, std::pair<float, std::vector<Texture*>>> animationMap;

public:
    explicit AniSprite();
    void CreateAnimation(const std::wstring& tag, int frameCount, float tickTime);
    bool PlayAnimation(const std::wstring& tag);
};