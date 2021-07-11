#pragma once
#include "TileMapManager.h"
#include "Scene.h"
class TileMapScene final :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

