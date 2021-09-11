#pragma once
#include "AniSprite.h"
#include "Singleton.h"

enum EffectTag
{
    E_BOMB,
    E_HIT,
    E_HEAL,
    E_DUST
};

class Effect :
    public AniSprite
{
public:
    EffectTag tag;
    Effect();

    void Update() override;
};

class EManager : public Singleton<EManager>
{
public:
    std::vector<Effect*> effects;
    void Create();
    void Spawn(Vec2 pos, EffectTag tag);
    void Delete();
};