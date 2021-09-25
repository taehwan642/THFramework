#pragma once
#include "Scene.h"

class Button;
class Font;

class OptionScene :
    public Scene
{
public:
    Button* toggleFull;
    Font* fullfont;

    Font* soundfont;

    Button* exit;

    void Init() override;
    void Update() override;
    void Exit() override;
};

