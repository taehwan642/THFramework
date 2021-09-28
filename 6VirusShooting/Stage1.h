#pragma once
#include "Scene.h"

class UIPack;

class Stage1 :
    public Scene
{
public:
    UIPack* pack;

    void Init();
    void Update();
    void Exit();
};

