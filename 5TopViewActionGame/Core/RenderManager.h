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
    { return a->layer < b->layer; }

public:
    __forceinline std::list<Object*>& 
        GetRenderObjects()
    {
        return renderObjects;
    }

    __forceinline void 
        AddRenderObjects(Object* obj)
    { 
        if (find(renderObjects.begin(), renderObjects.end(), obj) == renderObjects.end())
            renderObjects.emplace_back(obj);
        Sort();
    };
    
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