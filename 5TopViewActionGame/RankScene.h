#pragma once
#include "Scene.h"
class Sprite;
class Font;
class Button;

struct RankData
{
    char name[4];
    int score;
};

class RankScene :
    public Scene
{
public:
    bool isEntered = false;

    static std::vector<RankData> datas;
    static int score;
    static bool isCleared;

    char name[4]; // 3���� ���� + �ι���
    Font* fonts[5]; // ��ũ��
    Font* nameFont;
    Font* scoreFont;
    Button* returnButton;
    Sprite* back;

    void Init() override;
    void Update() override;
    void Exit() override;
};

