#pragma once
#include "Sprite.h"
class Font;
class CutScene :
    public Sprite
{
public:
    Font* font;
    // ÄÆ¾ÀÀÌ ½ÃÀÛµÇ±â Àü
    std::function<bool(void)> start;
    // ÄÆ¾ÀÀÌ ½ÃÀÛµÈ ÈÄ
    std::function<bool(void)> end;

    Vec3 currentRGB = { 0, 0, 0 };
    float tick = 0.0f;
    
    void Update() override;
    CutScene();
    virtual ~CutScene();
};

