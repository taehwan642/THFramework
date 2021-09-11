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

    friend HRESULT CALLBACK OnD3D9CreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
        void* pUserContext);
    friend void CALLBACK OnD3D9DestroyDevice(void* pUserContext);

protected:
    Texture* texture;

public:
    explicit Sprite() : texture(0) { RenderManager::GetInstance().AddRenderObjects(this); };

    __forceinline ~Sprite()
    { RenderManager::GetInstance().RemoveRender(this); };

    __forceinline void 
        SetTexture(const std::wstring& tag)
    {
        texture = TextureManager::GetInstance().LoadTexture(tag);
        SetRect(&imgRect, 0, 0, texture->info.Width, texture->info.Height);
    };

    __forceinline void
        SetTexture(Texture* texture)
    {
        this->texture = texture;
        SetRect(&imgRect, 0, 0, this->texture->info.Width, this->texture->info.Height);
    };

    [[nodiscard]] __forceinline const Texture*
        GetTexture() const
    {
        return texture;
    }

    void Lookat(Vec2 pos)
    {
        Vec2 temp = position - pos;
        rotation = atan2(temp.y, temp.x);
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
    
    void Render() override final;
};

