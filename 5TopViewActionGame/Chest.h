#pragma once
#include "AniSprite.h"
class Chest :
    public AniSprite
{
    // (�浹)�´°�
    // �ؽ�ó �ٲٴ� ���
    // hp
    int hp = 0;
    // ������ �Ѹ��� ���
public:
    Chest();
    void ItemSpawn();
    void Collide();
    void Update() override;
};

