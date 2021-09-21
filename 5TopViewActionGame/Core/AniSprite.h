#pragma once
#include "Sprite.h"
class AniSprite :
    public Sprite
{
private:
    std::wstring currentAnimationTag;
    std::pair<float, std::vector<Texture*>> currentAnimation;
    std::map<std::wstring, std::pair<float, std::vector<Texture*>>> animationMap;

protected:
    float currentTick;


public:
    int currentFrame;
    explicit AniSprite();
    void CreateAnimation(const std::wstring& tag, int frameCount, float tickTime);
    bool PlayAnimation(const std::wstring& tag);

    virtual float GetDeltaTime() { return DXUTGetElapsedTime(); }
};