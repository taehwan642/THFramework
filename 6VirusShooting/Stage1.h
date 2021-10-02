#pragma once
#include "Scene.h"

class UIPack;
class Player;

class Stage1 :
    public Scene
{
public:
    float monsterSpawnTime = 3.f;

    Player* player;
    UIPack* pack;

    void Init();
    void Update();
    void Exit();
};

