#pragma once
#include "GameObject.h"

enum MonsterTag
{
    M_SEAMONSTER,
    M_SKYMONSTER
};

class Monster :
    public GameObject
{
public:
    bool isBoss = false;
    float skilltime = 2.3f;
    MonsterTag type;

    void Boss1Pattern1();
    void Boss1Pattern2();

    Monster();
    void Dead() override;
    void CollideBullet();
    void Action() override;
};

class MonsterManager : public Singleton<MonsterManager>
{
public:
    std::vector<Monster*> m;
    void Create();
    void Spawn(Vec2 pos, MonsterTag type, bool isBoss = false);
    void Delete();
};

