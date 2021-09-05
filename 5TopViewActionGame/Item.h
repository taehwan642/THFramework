#pragma once
#include "Singleton.h"
#include "AniSprite.h"

enum ItemType
{
    I_HEAL,
    I_ATTACKUP,
    I_BOMB,
    I_HPUIUP,
    I_END
};

class Player;

class Item :
    public AniSprite
{
public:
    ItemType type;

    // 폭탄 전용 변수들
    Player* pl = nullptr;
    float tick = 2.f;
    float radius = 300.f;
    
    void Effect(Player* p);
    void Update() override;
};

class ItemManager : public Singleton<ItemManager>
{
public:
    std::vector<Item*> items;
    Player* pl = nullptr;
    // 생성
    void Create();
    // 스폰
    void Spawn(Vec2 pos);
    // 해제
    void Delete();
};