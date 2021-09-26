#pragma once
#include "GameObject.h"
#include "Singleton.h"

class Player;
enum BlockType;

class MonsterBullet : public GameObject
{
public:
    Vec2 dir{};
    float alivetime = 3.f;
    Player* player;
    MonsterBullet();
    void Action() override;
};


class MonsterBulletManager :
    public Singleton<MonsterBulletManager>
{
public:
    Player* p;
    std::vector<MonsterBullet*> mb;
    void Create();
    void Spawn(Vec2 pos, Vec2 dir, int damageval, BlockType type);
    void Delete();
};

