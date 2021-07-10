#pragma once
#include "Sprite.h"
#include "TileMapManager.h"
#include "Scene.h"
class MenuScene final :
    public Scene
{
private:
    //Sprite* block[30];

public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

