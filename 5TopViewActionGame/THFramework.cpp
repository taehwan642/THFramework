#include "DXUT.h"
#include "resource.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "TileMapManager.h"
#include "SoundManager.h"
#include "Monster.h"
#include "MonsterSpawner.h"
#include "Item.h"
#include "Effect.h"
#include "Bullet.h"

#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "Stage1.h"
#include "MainScene.h"
#include "Font.h"
#include "TilemapScene.h"
#include "EndingScene.h"
#include "IntroScene.h"
#include "RankScene.h"
#include "FailScene.h"
#include "OptionScene.h"

SceneManager& sm = SceneManager::GetInstance();
RenderManager& rm = RenderManager::GetInstance();

void LoadAni(std::wstring tag, int frameCount)
{
    for (int i = 0; i < frameCount; ++i)
    {
        const auto& route = tag + L" (" + std::to_wstring(i + 1) + L").png";
        TextureManager::GetInstance().LoadTexture(route);
    }
}

HRESULT CALLBACK 
OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    SM timeScale = 1.f;
    D3DXCreateSprite(DXUTGetD3D9Device(), &Sprite::sprite);
    Camera& c = Camera::GetInstance();
    c.Initialize();
    srand(time(NULL));

    std::thread th([&]() 
        {
            TextureManager& tm = TextureManager::GetInstance();
            std::wstring route;
            for (int i = 0; i < 8; ++i)
            {
                route = L"boom (" + std::to_wstring(i + 1) + L").png";
                tm.LoadTexture(route);
            }

            TileMapManager& tmm = TileMapManager::GetInstance();
            for (int i = 0; i < BlockType::PLAYER; ++i)
            {
                tm.LoadTexture(tmm.GetTextureTag((BlockType)i));
            }

            LoadAni(L"boss1idle", 10);

            return 0;
        });

    std::thread th2([&]()
        {
            // ¸ó½ºÅÍ

            SoundManager& smm = SoundManager::GetInstance();
            smm.LoadSound(L"Resources/Sound/Forest Birds 01.wav", L"bgm");
            return 0;
        });

    th.join();
    th2.join();
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

        MonsterManager::GetInstance().DeleteInstance();
        MonsterSpawnerManager::GetInstance().DeleteInstance();
        ItemManager::GetInstance().DeleteInstance();
        EManager::GetInstance().DeleteInstance();
        BManager::GetInstance().DeleteInstance();
    }
}

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
    DXUTCreateDevice( false, screenwidth, screenheight );
    
    sm.AddScene(L"Intro", new IntroScene);
    sm.AddScene(L"Main", new MainScene);
    sm.AddScene(L"Stage1", new Stage1);
    sm.AddScene(L"End", new EndingScene);
    sm.AddScene(L"Rank", new RankScene);
    sm.AddScene(L"Fail", new FailScene);
    sm.AddScene(L"Tilemap", new TilemapScene);
    sm.AddScene(L"Option", new OptionScene);
    sm.ChangeScene(L"Intro");

    DXUTMainLoop();

    return DXUTGetExitCode();
}


