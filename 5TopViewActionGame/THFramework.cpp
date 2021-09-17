#include "DXUT.h"
#include "resource.h"
#include "SceneManager.h"
#include "Texture.h"
#include "RenderManager.h"
#include "TileMapManager.h"
#include "Sprite.h"
#include "Camera.h"
#include "Stage1.h"
#include "MainScene.h"
#include "Font.h"
#include "TilemapScene.h"
#include "EndingScene.h"
#include "IntroScene.h"

SceneManager& sm = SceneManager::GetInstance();
RenderManager& rm = RenderManager::GetInstance();
bool isEnd = false;

HRESULT CALLBACK 
OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &Sprite::sprite);
    Camera& c = Camera::GetInstance();
    c.Initialize();
    srand(time(NULL));
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
    if (isEnd)
        return;
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

}

//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int 
main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );

    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9DeviceLost( OnLostDevice );

    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );

    DXUTInit( true, true );
    DXUTSetHotkeyHandling( true, true, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"THFramework" );
    DXUTCreateDevice( true, screenwidth, screenheight );
    
    sm.AddScene(L"Stage1", new Stage1);
    sm.AddScene(L"Tilemap", new TilemapScene);
    sm.AddScene(L"Main", new MainScene);
    sm.AddScene(L"Intro", new IntroScene);
    sm.AddScene(L"End", new EndingScene);
    sm.ChangeScene(L"End");

    DXUTMainLoop();

    isEnd = true;

    sm.ClearScenes();
    sm.DeleteInstance();

    TextureManager& tm = TextureManager::GetInstance();
    tm.ReleaseAllTexture();
    tm.DeleteInstance();

    TileMapManager& tmm = TileMapManager::GetInstance();
    tmm.DeleteInstance();

    rm.ClearAll();
    rm.DeleteInstance();

    Camera& c = Camera::GetInstance();
    c.DeleteInstance();

    Sprite::sprite->Release();

    return DXUTGetExitCode();
}


