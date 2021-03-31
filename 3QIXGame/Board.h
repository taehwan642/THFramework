#pragma once
#include "Pixel.h"
#include "VIM.h"
#include "Items.h"
#include "Virus.h"
#include "Effects.h"
#include "Sprite.h"

class Board :
    public Sprite
{
private:

    bool checkedPixels[50][50];
    bool showplayerpos = true; // debug

    PIXELDIRECTION direction;

    list<Pixel*> paths;
    list<Pixel*> clear1;
    list<Pixel*> clear2;

    float deltatime = 0.f;

    int item[5];

    void CheckBoard(int _posX, int _posY, int _index); // 어느 부분이 더 넒은지 확인
    void SpawnObsticle(int _posX, int _posY, OBSTICLETAG _tag); // 특정 위치에 장애물 스폰
    // 자르고 있을 때 바이러스랑 충돌하는지
    bool CheckPathPlayerAndVirusCollision(std::pair<int,int> _viruspos);
    // 자르고 있지 않을 때 바이러스랑 충돌하는지
    bool CheckPlayerAndVirusCollision(std::pair<int, int> _viruspos);
    // 바이러스가 내가 먹은 땅 속에 있는지
    bool CheckVirusInClearedArea(Pixel* _pixel, std::pair<int, int> _viruspos);
    // 먹은 땅을 모두 CLEARED로 채우고 item 스폰
    void PathstoClearAndSpawnItem(std::list<Pixel*> _list);
    // 플레이어 이동시키기
    void MovePlayer();

    void Initalize();

    bool clearedBoard = false;
protected:
public:
    float boardclear = 2.f;
    float cleartime = 180.f;
    VIM* vim = nullptr;

    int difficulty = 1;
    int score = 0;

    int pathStartposX = 0;
    int pathStartposY = 0;

    int backposX = 0; // 바로 직전
    int backposY = 0; // 바로 직전

    int playerX = 49;
    int playerY = 49;
    bool isCutting = false;

    Board(void);
    virtual ~Board(void);
    Pixel* pixels[50][50];
    void Update(void) override;

    void SetDifficulty(int _val);
};

