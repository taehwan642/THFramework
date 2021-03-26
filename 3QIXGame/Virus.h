#pragma once
#include "Sprite.h"
#include "Singleton.h"

class Virus :
    public Sprite
{
private:
    void SpeedMove();
    void BigMove();
    void FlashMove();
    void ToxinoMove();
    void CheckCollision();
    void SetRandomDirection(VIRUSDIRECTION _direction);
    void ToxinoAbility();
public:
    float delta = 0.f;
    float movespeed = 0.01f;
    int virusscale = 0;
    int speedX = 1;
    int speedY = 0;

    bool isHit = false;

    std::pair<int, int> pixelpos; // first = X, second = Y

    VIRUSTAG tag;
    VIRUSDIRECTION direction;

    Virus();
    virtual ~Virus();

    void Update() override;
};

class VirusManager :
    public Singleton<VirusManager>
{
private:
    int difficulty = 1;
public:
    Pixel* pixels[50][50];
    std::vector<Virus*> virusVector;
    void SetDifficulty(int _val);
    void CreateVirus();
    void SpawnVirus(Vec2 _position, int _startX, int _startY, VIRUSTAG _tag);
    void DeleteVirus();
};