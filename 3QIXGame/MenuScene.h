#pragma once
#include "Sprite.h"
#include "Font.h"
#include "Scene.h"
class MenuScene :
    public Scene
{
public:
    Sprite* buttons[5];

    Sprite* about = nullptr;
    Sprite* exitabout = nullptr;
    Sprite* items[4];
    Font* aboutfont[4];

    std::vector<std::pair<std::wstring, std::string>> aboutexamples;
    int currentIndex = 0;
    int maxIndex = 0;

    void Init() override; 
    void Update() override;
    void Exit() override;
};

