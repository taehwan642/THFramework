#pragma once
#include "TileMapManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "Scene.h"
class Stage1 final :
    public Scene
{
private:
    Player* player;
    MonsterManager& mm;

public:
    __forceinline 
        Stage1() : mm(MonsterManager::GetInstance()) {}
    void Init() override;
    void Update() override;
    void Exit() override;
};

