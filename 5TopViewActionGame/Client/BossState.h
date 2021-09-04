#pragma once
#include "GameObjectState.h"

enum class BossState
{
    IDLE,
    WALK,
    FOLLOW,
    ATTACK,
    ATTACK2,
    DEFENCE,
    DAMAGED,
    DIE
};

class BossIdleState :
    public GameObjectState
{
private:
    float idletime = 0.f;
public:
    explicit BossIdleState(GameObject* p) : GameObjectState(p) {};
    [[nodiscard]] int
        handleInput() override;
};

class BossWalkState :
    public GameObjectState
{
private:
    float walktime = 0.f;
    int xWay;
    bool isWalkStart = false;
public:
    explicit BossWalkState(GameObject* p) : GameObjectState(p) {};
    [[nodiscard]] int
        handleInput() override;
};


class BossFollowState :
    public GameObjectState
{
private:
public:
    explicit BossFollowState(GameObject* p) : GameObjectState(p) {};
    [[nodiscard]] int
        handleInput() override;
};