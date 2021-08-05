#pragma once
#include "TileMapManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "Minimap.h"
#include "Stage.h"
class Stage1 final :
    public Stage
{
private:
    

public:
    __forceinline 
        Stage1(){}
    void Init() override;
    void Update() override;
    void Exit() override;
};

