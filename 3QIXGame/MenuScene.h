#pragma once
#include "Sprite.h"
#include "Scene.h"
class MenuScene :
    public Scene
{
public:
    Sprite* buttons[5];

    void Init() override; 
    void Update() override;
    void Exit() override;
};

