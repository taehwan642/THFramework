#pragma once
#include "Scene.h"
class Sprite;

class MainScene :
    public Scene
{
public:
    Sprite* background;
    
    void Init() override;
    void Update() override;
    void Exit() override;
};