#pragma once
#include "Scene.h"
class Sprite;
class Button;

class MainScene :
    public Scene
{
public:
    Sprite* background;
    Button* Testbutton;

    void Init() override;
    void Update() override;
    void Exit() override;
};