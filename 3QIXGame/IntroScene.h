#pragma once
#include "Scene.h"
class IntroScene :
    public Scene
{
public:
    float delta = 0.f;
    void Init();
    void Update();
    void Exit();
};

