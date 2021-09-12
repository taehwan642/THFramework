#pragma once
#include "GameObject.h"

class Player :
    public GameObject
{
public:
    float spawnTime = 0.f;
    // float, float, float
    // ���ð�, ������, Ÿ��
    std::queue<std::pair<Vec4, std::vector<Vec2>>> bulletqueue;

    float aimTime = 0.f;
    Vec2 aimPos{ -999,-999 };

    POINT p;

    float attackupTick = 0.f;
    const int upAttack = 0;

    int score = 0;
    int hpuigauge = 0;

    int attackgauge = 10;

    Player();
    virtual ~Player() {};

    void HpUIUp(int healvalue); // ȸ�� ������ ȸ��
    
    void CollideItem();
    void CheckAttackUp();
    void Move();

    bool WeakShoot();
    bool SpecialWeakShoot();

    bool StrongShoot();
    bool SpecialStrongShoot();

    void Shoot();

    void Action() override;
};