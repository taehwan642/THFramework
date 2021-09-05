#pragma once
#include "Singleton.h"
class Camera final :
    public Singleton<Camera>
{
private:
    Matrix projM;
    Matrix worldM;
    Matrix viewM;

public:
    float camSize;
    Vec2 camPos;

    __forceinline void 
        Initialize() 
    {
        D3DXMatrixIdentity(&worldM);
        DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &worldM);
        camSize = 1;
        camPos = Vec2(0,0);
    };

    __forceinline Vec2
        GetPosition()
    {
        return camPos;
    }

    __forceinline void
        SetPosition(const Vec2& pos)
    {
        camPos = pos;
    }

    __forceinline void
        SetCameraSize(float size)
    {
        camSize = size;
    }

    void Update();

};

