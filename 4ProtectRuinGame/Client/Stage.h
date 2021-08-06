#pragma once
#include "TileMapManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "Minimap.h"
#include "Scene.h"

struct Map
{
    // �� ������������ �ο��� ����
    // 1. ���� ���� ������?
    // 2. ���� ���̵��� ������?
    // 3. �󸶳� ������?
    // 4. ���� ���������� �����ΰ�?
    // 5. ���� ���������� �� ������ ��� �Ǵ°�?
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