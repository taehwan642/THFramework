#pragma once
#include "GameObject.h"
#include "Singleton.h"

class Player;

class Bullet :
    public GameObject
{
public:
    Vec2 dir{};
    float alivetime = 3.f;
    Player* player;
    bool isWeak = false;

    Bullet();
    void UpGauge();
    void Action() override;
};

class BManager : public Singleton<BManager>
{
public:
    Player* player;
    std::vector<Bullet*> bullets;
    void Create();
    void Spawn(Vec2 pos, Vec2 mousepos, int damage, int spawntype = 0, bool isWeak = false);
    void Delete();
};