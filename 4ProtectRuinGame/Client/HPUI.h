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

    // imgrect�� ����ؼ� HP�� ��°� ǥ��
    void Update() override;
};

