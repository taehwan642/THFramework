#pragma once
#include "Singleton.h"
class Camera final :
    public Singleton<Camera>
{
private:
    Matrix om;
    Matrix im;
    Matrix vm;

    float camSize;
    Vec2 camPos;

public:
    void Initialize();
    void Update();

};

