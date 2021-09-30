#pragma once
#include "Singleton.h"

class Font;
class Sprite;

class MessageBoy :
    public Singleton<MessageBoy>
{
public:
    Font* text;
    Sprite* boy;
    Sprite* back;

    Vec2 pos[2];
    Vec2 startPos;
    Vec2 endPos;

    float tick = 0.f;
    bool isGoing = false; // �ڴ� ���̴� �ϴ� �����̳�?

    bool goBack = false; // �ڷ� ���ư���?

    void Create();
    void SpawnBoy(std::string textmsg); //
    void Update();
    void Delete();
};

