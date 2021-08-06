#pragma once
#include "TileMapManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "Minimap.h"
#include "Scene.h"

struct Map
{
    // 각 스테이지마다 부여될 정보
    // 1. 무슨 적이 나오나?
    // 2. 무슨 난이도로 나오나?
    // 3. 얼마나 나오나?
    // 4. 현재 스테이지는 무엇인가?
    // 5. 현재 스테이지의 맵 구성은 어떻게 되는가?
    std::string mapName;
    AniSprite* background;
    int difficulty;
    bool isCleared;
};

class Stage :
    public Scene
{
protected:
    Player* player;
    MonsterManager& mm;
    Minimap* minimap;

    AniSprite* door;

    void CheckPlayerInDoor();

public:
    Stage() : mm(MonsterManager::GetInstance()), currentStageindex(0) {}

    static std::vector<Map*> stages;
    int currentStageindex;

    void Init();
    void Update();
    void Exit();
};