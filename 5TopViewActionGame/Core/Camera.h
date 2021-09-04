#pragma once
#include "Singleton.h"
class Camera final :
    public Singleton<Camera>
{
private:
    Matrix projM;
    Matrix worldM;
    Matrix viewM;

    float camSize;
    Vec2 camPos;

public:
    __forceinline void 
        Initialize() 
    {
        D3DXMatrixIdentity(&worldM);
        DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &worldM);
        camSize = 1;
        camPos = { screenwidth / 2, screenheight / 2 };
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

