#pragma once
#include "Singleton.h"
#include "Object.h"

class RenderManager :
    public Singleton<RenderManager>
{
private:
    std::list<Object*> renderObjects;
    __forceinline static bool Comp(Object* a, Object* b) { return a < b; }

public:
    __forceinline void AddRenderObjects(Object* obj);
    __forceinline void DeleteRender(Object* obj);
    __forceinline void Sort();
    void Render();
};