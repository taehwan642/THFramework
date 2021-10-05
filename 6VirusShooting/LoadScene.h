#pragma once
#include "Scene.h"
class AniSprite;
class LoadScene :
    public Scene
{
public:
    void LoadAni(std::wstring tag, int startindex, int frameCount);
    void LoadStart();
    std::thread th4;
    std::thread th3;
    std::thread th;
    AniSprite* ans;
    void Init() override;
    void Update() override;
    void Exit() override;
};

