#pragma once
#include "Pixel.h"
#include "VIM.h"
#include "Items.h"
#include "Virus.h"
#include "Sprite.h"

class Board :
    public Sprite
{
private:
    int score = 0;

    bool checkedPixels[50][50];
    bool showplayerpos = true; // debug

    PIXELDIRECTION direction;

    list<Pixel*> paths;
    list<Pixel*> clear1;
    list<Pixel*> clear2;

    VIM* vim = nullptr;
    float deltatime = 0.f;

    int item[5];

    void CheckBoard(int _posX, int _posY, int _index);
    void SpawnObsticle(int _posX, int _posY, OBSTICLETAG _tag);
    bool CheckPathPlayerAndVirusCollision(std::vector<std::pair<int,int>> _viruspos); // bool return
    bool CheckPlayerAndVirusCollision(std::vector<std::pair<int, int>> _viruspos);

protected:
public:
    int difficulty = 1;

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

