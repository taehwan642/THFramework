#pragma once
#include "AniSprite.h"
class HPUI :
    public AniSprite
{
    // Ư�� ��ü���� �����Ǿ�� �ϰ�
    GameObject* obj;
    
    // HPBar, HPUI �ΰ��� �и��ؾ��ϰ� (Texture)
    AniSprite* bar;
    
    // �ִ� ü��, ���� ü�� ������ �˾ƾ� ��.
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

    // imgrect�� ����ؼ� HP�� ��°� ǥ��
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
