#pragma once
#include "Sprite.h"
#include "Scene.h"
class IntroScene :
    public Scene
{
public:
    Sprite* introsprite = nullptr;
    float delta = 0.f;
    void Init();
    void Update();
    void Exit();
};

