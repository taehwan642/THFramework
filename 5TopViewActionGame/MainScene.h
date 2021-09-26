#pragma once
#include "Scene.h"
class Sprite;
class Button;
class Font;

// 도움말에 들어갈 것.
struct HelpData
{
    std::wstring textag;
    std::string text;
};

class MainScene :
    public Scene
{
public:
    int index = 0;
    std::vector<HelpData> help;
    Sprite* helpBack;
    Button* helpButton;
    bool isHelpON = false;
    Button* helpExitButton;
    
    Sprite* helpui[4];
    Font* helpfont[4];

    Sprite* background;
    Button* Testbutton;
    Button* rankButton;
    Button* optionButton;
    Font* optionFont;

    Button* exitButton;

    void HelpActive(bool b);

    void Init() override;
    void Update() override;
    void Exit() override;
};