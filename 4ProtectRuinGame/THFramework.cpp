#include "DXUT.h"
#include "resource.h"
#include "SceneManager.h"
#include "Texture.h"
#include "MenuScene.h"

SceneManager& sm = SceneManager::GetInstance();

HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    return S_OK;
}

void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
   sm.UpdateScene();
}

void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
   sm.ClearScenes();
   sm.DeleteInstance();

   TextureManager::GetInstance().ReleaseAllTexture();
   TextureManager::GetInstance().DeleteInstance();
}

//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );

    DXUTInit( true, true );
    DXUTSetHotkeyHandling( true, true, true );
    DXUTSetCursorSettings( true, true );
    DXUTCreateWindow( L"THFramework" );
    DXUTCreateDevice( true, screenwidth, screenheight );

    sm.AddScene(L"Menu", new MenuScene);
    sm.ChangeScene(L"Menu");

    DXUTMainLoop();

    return DXUTGetExitCode();
}


