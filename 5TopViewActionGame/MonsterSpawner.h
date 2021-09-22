#pragma once
#include "Singleton.h"
#include "Sprite.h"

class MonsterSpawner :
    public Sprite
{
public:
    MonsterSpawner();
    virtual ~MonsterSpawner();

    int monsterSpawnValue = 3;
    std::vector<int> monsterType;
    float cooltime = 1.5f;
    float tick = 0.f;
    int difficulty = 1;

    void SetMonsterType(std::vector<int> type);
    void Update() override;
};

class MonsterSpawnerManager : public Singleton<MonsterSpawnerManager>
{
public:
    std::vector<MonsterSpawner*> spn;
    void Create();
    void Spawn(int spawnValue, std::vector<int> types, Vec2 position);
    void Delete();
};