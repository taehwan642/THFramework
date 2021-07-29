#pragma once
#include "GameObjectState.h"

enum class OctopusState
{
    IDLE,
    ATTACK,
    WALK,
    FOLLOW,
    DAMAGED
};

class OctopusIdleState final :
    public GameObjectState
{
    float idleTime;
public:
    explicit OctopusIdleState(GameObject* p) : 
        GameObjectState(p),
        idleTime(0.f)
    {};

    [[nodiscard]] int
        handleInput() override;
};

class OctopusAttackState final :
    public GameObjectState
{
    float deltatime;
public:
    explicit OctopusAttackState(GameObject* p) : GameObjectState(p), deltatime(0.f) {};
    [[nodiscard]] int
        handleInput() override;
};

class OctopusWalkState final :
    public GameObjectState
{
    float walktime;
    bool isWalkStart;
    int xWay;
public:
    explicit OctopusWalkState(GameObject* p) : 
        GameObjectState(p), 
        walktime(0.f), 
        isWalkStart(false), 
        xWay(0) {};

    [[nodiscard]] int
        handleInput() override;
};

class OctopusFollowState final :
    public GameObjectState
{
    float delta = 0.f;
public:
    explicit OctopusFollowState(GameObject* p) : GameObjectState(p) {};
    [[nodiscard]] int
        handleInput() override;
};

class OctopusDamagedState final :
    public GameObjectState
{
public:
    explicit OctopusDamagedState(GameObject* p) : GameObjectState(p) {};
    [[nodiscard]] int
        handleInput() override;
};