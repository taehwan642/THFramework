#pragma once
#include "AniSprite.h"
#include "Singleton.h"

class Bullet :
    public AniSprite
{
public:
    int damage = 1;
    Vec2 dir{};
    float speed = 400.f;
    float alivetime = 3.f;
    Bullet();

    void Update() override;
};

class BManager : public Singleton<BManager>
{
public:
    std::vector<Bullet*> bullets;
    void Create();
    void Spawn(Vec2 pos, Vec2 dir, int damage);
    void Delete();
};