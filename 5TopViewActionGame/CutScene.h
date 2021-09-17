#pragma once
#include "Sprite.h"
class Font;
class CutScene :
    public Sprite
{
public:
    Font* font;
    // �ƾ��� ���۵Ǳ� ��
    std::function<bool(void)> start;
    // �ƾ��� ���۵� ��
    std::function<bool(void)> end;

    Vec3 currentRGB = { 0, 0, 0 };
    float tick = 0.0f;
    
    void Update() override;
    CutScene();
    virtual ~CutScene();
};

