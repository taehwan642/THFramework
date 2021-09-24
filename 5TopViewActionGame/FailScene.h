#pragma once
#include "Scene.h"

class Sprite;
class Button;
class Font;

class FailScene :
    public Scene
{
public:
    Sprite* back;
    Button* restart;
    Button* exit;

    Font* font;

    void Init() override;
    void Update() override;
    void Exit() override;
};

