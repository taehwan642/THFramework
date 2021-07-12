#pragma once
#include "TileMapManager.h"
#include "Player.h"
#include "Scene.h"
class Stage1 final :
    public Scene
{
private:
    Player* player;
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

