#pragma once
#include "Singleton.h"
#include "AniSprite.h"
enum EffectType
{
    E_AIRSUPPORT,
    E_EXPLOSION
};

class Effect :
    public AniSprite
{
public:
    EffectType type;
    Effect();
    void Update() override;
};

class EffectManager : public Singleton<EffectManager>
{
public:
    std::vector<Effect*> eff;
    void Create();
    Effect* Spawn(Vec2 pos, EffectType type);
    void Delete();
};