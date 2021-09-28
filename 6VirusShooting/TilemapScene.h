#pragma once
#include "Scene.h"
class TilemapScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

