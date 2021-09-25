#pragma once
#include "GameObject.h"

struct ShootData
{
    std::vector<Vec2> dir; // �ΰ��� �뵵
    int damage;
    int spawntype;
    bool isweak;
    float spawntime;
};

enum PlayerState
{
    IDLE, SHOOT, SHOTGUN, LUCIAN
};

class Player :
    public GameObject
{
public:
    PlayerState state = IDLE;

    float spawnTime = 0.f;
    // float, float, float
    // ���ð�, ������, Ÿ��
    std::queue<ShootData> bulletqueue;

    float aimTime = 0.f;
    Vec2 aimPos{ -999,-999 };

    POINT p;

    float attackupTick = 0.f;
    const int upAttack = 0;

    int score = 0;
    int hpuigauge = 0;

    int attackgauge = 0;

    void ChangeState(PlayerState s)
    {
        if (state != SHOOT && state != SHOTGUN && state != LUCIAN)
            state = s;
    }

    Player();
    virtual ~Player() {};

    bool invincible = false;
    void Damaged(int damage) override;

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