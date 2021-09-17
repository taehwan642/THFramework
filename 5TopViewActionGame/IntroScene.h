#pragma once
#include "Scene.h"

class CutScene;

class IntroScene :
    public Scene
{
public:
    std::function<bool(void)> cutsceneFunc;
    bool isStart = true;
    int cutsceneindex = 0;
    CutScene* cutscene[6];
    void Init() override;
    void Update() override;
    void Exit() override;
};