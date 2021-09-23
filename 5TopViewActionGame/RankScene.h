#pragma once
#include "Scene.h"
class RankScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

