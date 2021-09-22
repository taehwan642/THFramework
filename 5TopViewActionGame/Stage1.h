#pragma once
#include "Scene.h"

class Player;
class UIPack;
class Chest;
class Monster;

class Stage1 :
    public Scene
{
    Player* p;
    UIPack* uipack;
    std::vector<Monster*> monsters;

    std::vector<Chest*> chests;

public:
    void Init() override;
    void Update() override;
    void Exit() override;
};

