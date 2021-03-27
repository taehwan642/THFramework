#pragma once
#include "Font.h"
#include "Scene.h"
class RankingScene :
    public Scene
{
public:
    bool isentered = false;
    Font* fonts[5];
    Font* nameFont = nullptr;
    Font* scoreFont = nullptr;
    Font* returnFont = nullptr;
    char name[4];

    void Init() override;
    void Update() override;
    void Exit() override;
};

