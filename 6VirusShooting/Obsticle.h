#pragma once
#include "AniSprite.h"

class Player;

enum ObsticleType
{
    O_MINEOBS,
    O_TRASHOBS,
    O_END
};

class Obsticle :
    public AniSprite
{
public:
    Player* player;
    ObsticleType type;
    int hp = 5;
    int trashtype = 0;
    float movespeed = 100.f;
    Obsticle();

    void CollideWithBullet();
    void CollideWithPlayer();
    
    void Update() override;
};

class ObsticleManager : public Singleton<ObsticleManager>
{
public:
    Player* player;
    std::vector<Obsticle*> o;
    void Create();
    void Spawn(Vec2 pos, ObsticleType type);
    void Delete();
};