#pragma once
#include "Scene.h"

class Player;
class UIPack;
class Chest;
class Monster;
class MonsterSpawner;
class Door;
class Button;
class Boss1;

struct MapTXTData
{
    std::string blockTXT;
    std::string objTXT;
};

class Stage1 :
    public Scene
{
    std::vector<MapTXTData> mapTXTdata;
    Player* p;
    UIPack* uipack;
    std::vector<Chest*> chests;
    Door* door;

    Sprite* blur = nullptr;

    Button* mainButton;
    Button* restartButton;

    int difficulty = 1;

    int currentStage = 0;
    int stagedatas[3]{};

    bool isPaused = false;

    void CheatKey();

    void Initialize(); // ¸Ê ¹Ù²ð¶§¸¶´Ù
    void SetMap(int index);

public:
    void Init() override;
    void Update() override;
    void Exit() override;
};