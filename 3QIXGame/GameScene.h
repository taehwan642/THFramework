#pragma once
#include "Board.h"
#include "Scene.h"
class GameScene :
    public Scene
{
public:
    Sprite* back = nullptr;
    Board* b = nullptr;
    void Init() override;
    void Update() override;
    void Exit() override;
};

