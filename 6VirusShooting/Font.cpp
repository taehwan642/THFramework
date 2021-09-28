#include "DXUT.h"
#include "Font.h"
#include "Texture.h"
#include "RenderManager.h"

void Font::Adapt(Vec2 pos, Texture* tex, Vec2 sc, Vec2 intv)
{
    position = { pos.x, pos.y };
    // �Ǻ��� ������ 0.5��� ���� �Ͽ� ����ȴ�.
    // x�� ��ư�� ũ�⸸ŭ ���ְ�, y�� ��ư�� ũ�⸸ŭ ���ָ� (�÷��ָ�) �ȴ�.
    position.x -= ((tex->info.Width / 2) * sc.x) - intv.x;
    position.y -= ((tex->info.Height / 2) * sc.y) - intv.y;
}

Font::Font(float scale, float weight, LPCWSTR path)
{
	memset(buffer, '\0', sizeof(char) * 256);
	// ������ �⺻ ũ��
	// weight = ����
	// 
	D3DXCreateFont(DXUTGetD3D9Device(), 20 * scale, 0, weight, 1, false,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, path, &font);
/*
    D3DXCreateFontW(
        LPDIRECT3DDEVICE9       pDevice,
        INT                     Height, // ũ��
        UINT                    Width, // ����
        UINT                    Weight, // ����
        UINT                    MipLevels, // 1
        BOOL                    Italic, // false
        DWORD                   CharSet, // 1
        DWORD                   OutputPrecision, // OUT_DEFUALT_PRESIS, 0
        DWORD                   Quality, // proof quality
        DWORD                   PitchAndFamily, // default_pitch, ff_dontcare
        LPCWSTR                 pFaceName, // ��Ʈ �̸�
        LPD3DXFONT*             ppFont); // ����

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
    // buffer���ٰ� ���ڷ� ���� text�� ����
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
    // font�� ��ġ�� rect�� �����Ǳ� ������ position�� ��ġ�� ��Ʈ���� �ѱ�
    // �׷� font�� position�� �����ϰ� ��.
    
    font->DrawTextA(nullptr, buffer, -1, &r, DT_NOCLIP, color);
}
