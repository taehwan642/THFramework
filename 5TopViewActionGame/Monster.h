#pragma once
#include "Singleton.h"
#include "GameObject.h"

enum BlockType;

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

    virtual void HPUIUpdate();

    virtual void Follow() {};
    virtual void CheckCanAttack() {};

    void Action() override;

    virtual void SetStat(int diff) {}; // 난이도에 의존하는 스탯 초기화

    virtual bool IdleState() { return true; };
    virtual bool AttackState() { return true; };

    void CollideMonsters();
};

class MonsterManager : public Singleton<MonsterManager>
{
public:
    Player* p;
    std::vector<Monster*> monsters;
    void Create();
    void Spawn(BlockType type, Vec2 position, int difficulty = 1);
    void Delete();
};