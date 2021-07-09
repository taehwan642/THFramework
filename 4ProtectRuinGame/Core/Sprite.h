#pragma once
#include "Object.h"
class Sprite :
    public Object
{
private:
    static LPD3DXSPRITE sprite;
    Texture* texture;

public:
    __forceinline Sprite() : texture(0)
    {
        D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
    };

    __forceinline ~Sprite()
    {
        RenderManager::GetInstance().RemoveRender(this);
    };

    __forceinline void SetTexture(std::wstring tag)
    {
        texture = TextureManager::GetInstance().LoadTexture(L"this");
        RenderManager::GetInstance().AddRenderObjects(this);
    };

    __forceinline RECT GetRect() const
    {
        return RECT();
    }   
    
    void Render() override;
};

LPD3DXSPRITE Sprite::sprite = nullptr;