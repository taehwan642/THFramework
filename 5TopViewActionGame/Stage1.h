#pragma once
#include "Scene.h"

class Player;
class UIPack;
class Chest;
class Monster1;

class Stage1 :
    public Scene
{
    Player* p;
    UIPack* uipack;
    Monster1* m;

    std::vector<Chest*> chests;

public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

