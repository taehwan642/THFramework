#pragma once
#include "AniSprite.h"
class HPUI :
    public AniSprite
{
    // 특정 객체에게 부착되어야 하고
    GameObject* obj;
    
    // HPBar, HPUI 두개로 분리해야하고 (Texture)
    AniSprite* bar;
    
    // 최대 체력, 현재 체력 정보를 알아야 함.
    int MaxHP;
    int HP;

    float up;

public:
    HPUI(const std::wstring& tag, const std::wstring& bartag);

    __forceinline void SetMaxHP(int maxhp);
    __forceinline void SetHP(int hp);

    __forceinline void SetUp(float up);
    __forceinline float GetUp();

    __forceinline void SetHPBarPos();

    // imgrect를 사용해서 HP가 닳는걸 표현
    void Update() override;
};

void HPUI::SetMaxHP(int maxhp)
{
    MaxHP = maxhp;
}

void HPUI::SetHP(int hp)
{
    HP = hp;
}

void HPUI::SetUp(float up)
{
    this->up = up;
}

float HPUI::GetUp()
{
    return up;
}

void HPUI::SetHPBarPos()
{
    bar->position = position;
}
