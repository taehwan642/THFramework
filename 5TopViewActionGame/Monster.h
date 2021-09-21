#pragma once
#include "GameObject.h"

enum MonsterState
{
    M_IDLE,
    M_ATTACK
};

class Player;

class Monster :
    public GameObject
{
public:
    Monster();
    virtual ~Monster();
    Sprite* hpui = nullptr;
    Sprite* hpuibar = nullptr;

    Player* player;
    MonsterState state = M_IDLE;

    void CollideBullet();

    void HPUIUpdate();

    virtual void Follow() {};
    virtual void Attack() {};

    void Action() override;

    virtual bool IdleState() { return true; };
    virtual bool AttackState() { return true; };
};

