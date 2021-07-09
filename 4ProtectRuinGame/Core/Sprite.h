#pragma once
#include "DXUT.h"
#include "Texture.h"
#include "RenderManager.h"
#include "Object.h"

class Sprite :
    public Object
{
private:
    static LPD3DXSPRITE sprite;
    Texture* texture;

    friend HRESULT CALLBACK OnD3D9CreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
        void* pUserContext);
    friend void CALLBACK OnD3D9DestroyDevice(void* pUserContext);

public:
    Sprite() : texture(0) {};

    __forceinline ~Sprite()
    { RenderManager::GetInstance().RemoveRender(this); };

    __forceinline void 
        SetTexture(std::wstring tag)
    {
        texture = TextureManager::GetInstance().LoadTexture(tag);
        SetRect(&imgRect, 0, 0, texture->info.Width, texture->info.Height);
        RenderManager::GetInstance().AddRenderObjects(this);
    };

    [[nodiscard]] __forceinline const Texture*
        GetTexture() const
    {
        return texture;
    }

    [[nodiscard]] __forceinline RECT
        GetRect() const
    {
        RECT r;
        r.right = position.x + (texture->info.Width / 2 * scale.x);
        r.left = position.x - (texture->info.Width / 2 * scale.x);
        r.top = position.y - (texture->info.Height / 2 * scale.y);
        r.bottom = position.y + (texture->info.Height / 2 * scale.y);
        return r;
    };
    
    void Render() override
    {
        if (isactive == false)
            return;

        if (texture == nullptr)
            return;

        sprite->Begin(D3DXSPRITE_ALPHABLEND);
        sprite->SetTransform(&GetMatrix());
        Vec3 center = {
            texture->info.Width * pivot.x,
            texture->info.Height * pivot.y,
            0 };
        sprite->Draw(texture->texture, &imgRect, &center, nullptr, color);
        sprite->End();
    };
};

