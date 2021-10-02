#pragma once
#include "AniSprite.h"

class Player;

enum ItemType
{
    I_MACHINEGUNBULLET,
    I_TORPEDO,
    I_MISSILE,
    I_BOOSTER,
    I_TOOLBOX,
    I_EVENTBOX,
    I_END
};

class Item :
    public AniSprite
{
private:
    void MachineGunBullet();
    void Torpedo();
    void Missile();
    void Booster();
    void Toolbox();
    void Eventbox();

    void CollideWithPlayer();
public:
    Player* player;
    ItemType type;
    float movespeed = 100.f;
    Item();
    void Update() override;
};

class ItemManager : public Singleton<ItemManager>
{
public:
    Player* player;
    std::vector<Item*> it;
    void Create();
    void Spawn(Vec2 pos, ItemType type);
    void Delete();
};