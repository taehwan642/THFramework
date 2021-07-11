#pragma once
#include "Singleton.h"
#include "Object.h"

class RenderManager :
    public Singleton<RenderManager>
{
private:
    std::list<Object*> renderObjects;

    __forceinline static bool 
        Comp(Object* a, Object* b) 
    { return a < b; }

public:
    __forceinline void 
        AddRenderObjects(Object* obj)
    { renderObjects.emplace_back(obj); };
    
    __forceinline void 
        RemoveRender(Object* obj)
    { renderObjects.remove(obj); };
    
    __forceinline void 
        Sort()
    { renderObjects.sort(Comp); };
    
    void Render() 
    {
        for (auto& iter : renderObjects)
        {
            iter->Update();
            iter->Render();
        }
    };

    __forceinline void
        ClearAll()
    {
        renderObjects.clear();
    };
};