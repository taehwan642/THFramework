#pragma once
#include "Singleton.h"
#include "AniSprite.h"

enum class Effects
{
    DUST,
    HEAL,
    HIT
};

class Effect :
    public AniSprite
{
public:
    Effects effect;
    Effect();
    void Update() override;
};

class EffectManager :
    public Singleton<EffectManager>
{
private:
    std::vector<Effect*> effects;

public:
    void CreateEffect();
    void SpawnEffect(Effects effect, const Vec2& position);
    void DeleteEffect();
};