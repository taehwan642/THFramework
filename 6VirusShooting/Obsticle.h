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
    Sprite* radius = nullptr;
    int hp = 10;
    int trashtype = 0;
    float movespeed = 80.f;
    Obsticle();
    virtual ~Obsticle();
    // RAII 생성자에서 리소스 할당
    // 소멸자에서 리소스 해제

    void Mine();
    void Trash();

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