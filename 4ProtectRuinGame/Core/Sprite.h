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

    friend void CALLBACK OnD3D9DestroyDevice(void* pUserContext);

public:
    Sprite() : texture(0)
    { D3DXCreateSprite(DXUTGetD3D9Device(), &sprite); };

    __forceinline ~Sprite()
    { RenderManager::GetInstance().RemoveRender(this); };

    __forceinline void 
        SetTexture(std::wstring tag)
    {
        texture = TextureManager::GetInstance().LoadTexture(tag);
        SetRect(&imgRect, 0, 0, texture->info.Width, texture->info.Height);
        RenderManager::GetInstance().AddRenderObjects(this);
    };

    __forceinline RECT
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

