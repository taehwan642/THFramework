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

    // ��ź ���� ������
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
    // ����
    void Create();
    // ����
    void Spawn(Vec2 pos);
    // ����
    void Delete();
};