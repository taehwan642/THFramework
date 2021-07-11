#pragma once
#include "Sprite.h"
#include "Scene.h"
class MenuScene final :
    public Scene
{
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

