#include "DXUT.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TileMapScene.h"

void 
TileMapScene::Init()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	tmm.Initialize();

	Camera& cam = Camera::GetInstance();
	cam.Initialize();
}

void 
TileMapScene::Update()
{
	TileMapManager& tmm = TileMapManager::GetInstance();
	Camera& cam = Camera::GetInstance();

	Vec2 camPos = cam.GetPosition();

	if (DXUTIsKeyDown('W'))
	{
		camPos.y -= 100.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('S'))
	{
		camPos.y += 100.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('A'))
	{
		camPos.x -= 100.f * DXUTGetElapsedTime();
	}
	if (DXUTIsKeyDown('D'))
	{
		camPos.x += 100.f * DXUTGetElapsedTime();
	}

	cam.SetPosition(camPos);

	tmm.UpdateManager();

	if (DXUTWasKeyPressed('O'))
		tmm.SaveBlocks();

	if (DXUTWasKeyPressed('M'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void 
TileMapScene::Exit()
{

}
