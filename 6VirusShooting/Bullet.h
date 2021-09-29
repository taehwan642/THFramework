#pragma once
#include "Singleton.h"
#include "AniSprite.h"

enum BulletType
{
    B_MACHINEGUNBULLET,
    B_NAVALGUNBULLET
};

class Bullet :
    public AniSprite
{
public:
    BulletType type;
    Vec2 dir;
    float movespeed = 1000.f;
    Bullet();
    void Move();
    void Update() override;
};

class BulletManager : public Singleton<BulletManager>
{
public:
    std::vector<Bullet*> b;
    void Create();
    void Spawn(Vec2 pos, Vec2 dir, BulletType type);
    void Delete();
};