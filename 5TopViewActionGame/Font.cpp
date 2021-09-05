#include "DXUT.h"
#include "Font.h"
#include "RenderManager.h"

Font::Font(float scale, float weight, LPCWSTR path)
{
	memset(buffer, '\0', sizeof(char) * 256);
	// 스케일 기본 크기
	// weight = 굵기
	// 
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, false,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, path, &font);
/*
    D3DXCreateFontW(
        LPDIRECT3DDEVICE9       pDevice,
        INT                     Height, // 크기
        UINT                    Width, // 무시
        UINT                    Weight, // 굵기
        UINT                    MipLevels, // 1
        BOOL                    Italic, // false
        DWORD                   CharSet, // 1
        DWORD                   OutputPrecision, // OUT_DEFUALT_PRESIS, 0
        DWORD                   Quality, // proof quality
        DWORD                   PitchAndFamily, // default_pitch, ff_dontcare
        LPCWSTR                 pFaceName, // 폰트 이름
        LPD3DXFONT*             ppFont); // 리턴

*/
    RenderManager::GetInstance().AddRenderObjects(this);
}

Font::~Font()
{
    font->Release();
    RenderManager::GetInstance().RemoveRender(this);
}

void Font::SetText(char* text)
{
    // buffer에다가 인자로 들어온 text값 복사
    sprintf(buffer, text);
}

void Font::Render()
{
    if (isactive == false)
        return;

    if (font == nullptr)
        return;

    RECT r;
    SetRect(&r, (long)position.x, (long)position.y, 0, 0);
    // font의 위치는 rect로 결정되기 때문에 position의 위치를 렉트에다 넘김
    // 그럼 font는 position에 의존하게 됨.
    
    font->DrawTextA(nullptr, buffer, -1, &r, DT_NOCLIP, color);
}
