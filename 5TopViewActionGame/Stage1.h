#pragma once
#include "Scene.h"

class Player;
class UIPack;

class Stage1 :
    public Scene
{
    Player* p;
    UIPack* uipack;
public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

