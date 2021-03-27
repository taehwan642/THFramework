#pragma once
#include "Singleton.h"
#include "Sprite.h"
class Effects :
    public Sprite
{
public:
    EFFECTTAG tag;
    Effects();
    virtual ~Effects();

    void Update() override;
};

class EffectManager :
    public Singleton<EffectManager>
{
public:
    std::vector<Effects*> effects;
    void CreateEffect();
    void SpawnEffect(Vec2 _position, EFFECTTAG _tag);
    void DeleteEffect();
};