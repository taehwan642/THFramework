#include "DXUT.h"
#include "resource.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "TileMapManager.h"
#include "SoundManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "Stage1.h"
#include "Font.h"
#include "Stage1.h"

// 무기 아이템 연결
// 총알 데미지 추가
// 나머지 총알, 무기, 아이템
// 관련된 UI 모두 제작
// 스킬
// 적
// 스테이지
// 씬 플로우
// 사운드 추가
// 마무리

SceneManager& sm = SceneManager::GetInstance();
RenderManager& rm = RenderManager::GetInstance();

void LoadAni(std::wstring tag, int startindex, int frameCount)
{
    for (int i = startindex; i < frameCount; ++i)
    {
        const auto& route = tag + L" (" + std::to_wstring(i + 1) + L").png";
        TextureManager::GetInstance().LoadTexture(route);
    }
}

HRESULT CALLBACK 
OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    Time::timescale = 1.f;
    D3DXCreateSprite(DXUTGetD3D9Device(), &Sprite::sprite);
    Camera& c = Camera::GetInstance();
    c.Initialize();
    srand(time(NULL));

    std::thread th([&]() 
        {
            LoadAni(L"Sprites/effect/AirSupprt/airsupport", 0, 15);
            LoadAni(L"Sprites/player/move/6/move", 0, 15);
            return 0;
        });

    std::thread th2([&]()
        {
            LoadAni(L"Sprites/effect/explo/explosion", 23,0);
            LoadAni(L"Sprites/effect/AirSupprt/airsupport", 15, 20);
            return 0;
        });

    std::thread th3([&]()
        {
            LoadAni(L"Sprites/effect/AirSupprt/airsupport", 20, 31);
            LoadAni(L"Sprites/player/move/6/move", 15, 30);
            return 0;
        });

    std::thread th4([&]() {
           LoadAni(L"Sprites/bullet/mine/mine",0, 30);
           LoadAni(L"Sprites/bullet/Garbage/type1/trash", 0, 30);
           LoadAni(L"Sprites/bullet/Garbage/type2/trash", 0, 30);
           LoadAni(L"Sprites/Item/toolbox/toolbox", 0, 30);
           LoadAni(L"Sprites/Item/eventbox/eventbox", 0, 30);
           return 0;
        });

    th.join();
    th2.join();
    th3.join();
    th4.join();
    return S_OK;
}

HRESULT CALLBACK OnD3D9ResetDevice(IDirect3DDevice9* pd3dDevice,
    const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
    HRESULT hr;
    Sprite::sprite->OnResetDevice();
    std::list<Object*>& list = rm.GetRenderObjects();
    for (auto iter : list)
    {
        Font* f = dynamic_cast<Font*>(iter);
        if (f != nullptr)
            f->font->OnResetDevice();
    }
    return S_OK;
}

void CALLBACK OnLostDevice(void* pUserContext)
{
    Sprite::sprite->OnLostDevice();
    std::list<Object*>& list = rm.GetRenderObjects();
    for (auto iter : list)
    {
        Font* f = dynamic_cast<Font*>(iter);
        if (f != nullptr)
            f->font->OnLostDevice();
    }
}

void CALLBACK 
OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    Time::dt = fElapsedTime * Time::timescale;
    sm.UpdateScene();
}

void CALLBACK 
OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        rm.Render();
        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK 
OnD3D9DestroyDevice( void* pUserContext )
{
    if (SceneManager::GetInstance().deviceEnd == true)
    {
        sm.ClearScenes();
        sm.DeleteInstance();

        TextureManager& tm = TextureManager::GetInstance();
        tm.ReleaseAllTexture();
        tm.DeleteInstance();

        TileMapManager& tmm = TileMapManager::GetInstance();
        tmm.DeleteBlocks();
        tmm.DeleteInstance();

        rm.ClearAll();
        rm.DeleteInstance();

        Camera& c = Camera::GetInstance();
        c.DeleteInstance();

        Sprite::sprite->Release();

        SoundManager& smm = SoundManager::GetInstance();
        smm.DeleteSounds();
        smm.DeleteInstance();
    }
}

// 창 -> 주석풀기
//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    //_CrtSetBreakAlloc(316);

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );

    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9DeviceLost( OnLostDevice );

    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );

    DXUTInit( true, true );
    DXUTSetHotkeyHandling( true, false, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"THFramework" );
    // false 세팅
    DXUTCreateDevice( true, screenwidth, screenheight );
    
    sm.AddScene(L"Stage1", new Stage1);
    sm.ChangeScene(L"Stage1");

    DXUTMainLoop();

    return DXUTGetExitCode();
}


