#pragma once
#include "Scene.h"
class RankingScene :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

